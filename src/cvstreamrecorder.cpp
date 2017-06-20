// Based off of LibSourcey's scy::StreamRecorder.

#include "cvstreamrecorder.h"

#ifdef HAVE_FFMPEG

#include "scy/logger.h"

namespace scy {

	CvStreamRecorder::CvStreamRecorder(int targetWidth, int targetHeight, std::function<void(cv::Mat &)> callback)
		: _targetWidth(targetWidth)
		, _targetHeight(targetHeight)
		, _awaitingVideo(false)
		, _awaitingAudio(false)
		, _videoEnabled(false)	// Initially, no handling of video or audio. Caller must first call setVideoTrack() and/or setAudioTrack().
		, _audioEnabled(false)
		, _onNewRGBFrameCallback(callback)
	{
	}

	CvStreamRecorder::~CvStreamRecorder()
	{
		if (_videoTrack)
			_videoTrack->RemoveSink(this);

		if (_audioTrack)
			_audioTrack->RemoveSink(this);
	}

	void CvStreamRecorder::setVideoTrack(webrtc::VideoTrackInterface* track)
	{
		assert(!_videoTrack);
		_videoTrack = track;
		_videoTrack->AddOrUpdateSink(this, rtc::VideoSinkWants());
		_videoEnabled = true;
		_awaitingVideo = true;
	}


	void CvStreamRecorder::setAudioTrack(webrtc::AudioTrackInterface* track)
	{
		assert(!_audioTrack);
		_audioTrack = track;
		_audioTrack->AddSink(this);
		_audioEnabled = true;
		_awaitingAudio = true;
	}


	void CvStreamRecorder::OnFrame(const webrtc::VideoFrame& yuvframe)
	{
		LTrace("On video frame: ", yuvframe.width(), 'x', yuvframe.height())

		if (_awaitingVideo) {
			_awaitingVideo = false;

			// allocate the destination Mat
			_resizedRGBFrame = cv::Mat(_targetHeight, _targetWidth, CV_8UC3);
		}

		int yuvFrameWidth = yuvframe.width();
		int yuvFrameHeight = yuvframe.height();

		auto yDataPointer = (uint8_t*)yuvframe.video_frame_buffer()->DataY();
		auto uDataPointer = (uint8_t*)yuvframe.video_frame_buffer()->DataU();
		auto vDataPointer = (uint8_t*)yuvframe.video_frame_buffer()->DataV();

		// we can do this because the YUV data is all contiguous (Y then U then V)
		cv::Mat yuvMat(yuvFrameHeight + yuvFrameHeight / 2, yuvFrameWidth, CV_8UC1, yDataPointer);	

		cv::cvtColor(yuvMat, _convertedRGBFrame, CV_YUV420p2RGB);

		cv::resize(_convertedRGBFrame, _resizedRGBFrame, cv::Size(_targetWidth, _targetHeight));

		_onNewRGBFrameCallback(_resizedRGBFrame);
	}


	void CvStreamRecorder::OnData(const void* audio_data, int bits_per_sample,
		int sample_rate, size_t number_of_channels,
		size_t number_of_frames)
	{
		STrace << "On audio frame: "
			<< "number_of_frames=" << number_of_frames << ", "
			<< "number_of_channels=" << number_of_channels << ", "
			<< "sample_rate=" << sample_rate << ", "
			<< "bits_per_sample=" << bits_per_sample << std::endl;

		STrace << "TODO: ignoring all incoming audio data" << std::endl;
	}
}

#endif // HAVE_FFMPEG