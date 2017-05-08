// Based off of LibSourcey's scy::StreamRecorder.
// Acts as a video (and eventually audio -- TODO) sink for incoming WebRTC data
// but instead of encoding the data to a video file, it converts them into
// OpenCV Mats (resizing them consistently) and passes them to a custom 
// callback function.

#ifndef CvStreamRecorder_H
#define CvStreamRecorder_H

#include "scy/av/av.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <functional>

#ifdef HAVE_FFMPEG

#include "webrtc/api/peerconnectioninterface.h"

namespace scy {

	class CvStreamRecorder : public rtc::VideoSinkInterface<webrtc::VideoFrame>,
		public webrtc::AudioTrackSinkInterface
	{
	public:
		CvStreamRecorder(int targetWidth, int targetHeight, std::function<void(cv::Mat &)> callback);
		~CvStreamRecorder();

		void setVideoTrack(webrtc::VideoTrackInterface* track);
		void setAudioTrack(webrtc::AudioTrackInterface* track);

		/// VideoSinkInterface implementation
		void OnFrame(const webrtc::VideoFrame& frame) override;

		/// AudioTrackSinkInterface implementation
		void OnData(const void* audio_data, int bits_per_sample, int sample_rate,
			size_t number_of_channels, size_t number_of_frames) override;
	protected:
		rtc::scoped_refptr<webrtc::VideoTrackInterface> _videoTrack;
		rtc::scoped_refptr<webrtc::AudioTrackInterface> _audioTrack;
		bool _awaitingVideo;
		bool _awaitingAudio;

		// resolution of frames after receiving them via WebRTC and resizing them
		int _targetWidth;
		int _targetHeight;

		// flags determining whether this streamrecorder will do anything with incoming video or audio
		bool _videoEnabled;
		bool _audioEnabled;

		cv::Mat _convertedRGBFrame;	// for converting from YUV to RGB
		cv::Mat _resizedRGBFrame;	// for resizing converted RGB to target size RGB

		std::function<void(cv::Mat &)> _onNewRGBFrameCallback;
	};

}
#endif // HAVE_FFMPEG
#endif