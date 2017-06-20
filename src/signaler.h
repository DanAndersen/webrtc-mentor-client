///
//
// LibSourcey
// Copyright (c) 2005, Sourcey <http://sourcey.com>
//
// SPDX-License-Identifier:	LGPL-2.1+
//
///


#ifndef SCY_WebRTC_Signaler_H
#define SCY_WebRTC_Signaler_H


#include "config.h"
#include "scy/application.h"
#include "scy/ipc.h"
#include "scy/net/sslmanager.h"
#include "scy/net/sslsocket.h"
#include "scy/symple/client.h"
#include "scy/webrtc/peermanager.h"
#include "scy/webrtc/streamrecorder.h"

#include "cvstreamrecorder.h"

#include <iostream>
#include <string>


namespace scy {


class Signaler : public wrtc::PeerManager, public Application
{
public:
    Signaler(const smpl::Client::Options& options);
    ~Signaler();

	void onNewRGBFrame(cv::Mat& frame);

	cv::Mat _rgbFrame;
	bool _hasNewFrame = false;

protected: 

    /// PeerConnectionManager interface
    void sendSDP(wrtc::Peer* conn, const std::string& type, const std::string& sdp);
    void sendCandidate(wrtc::Peer* conn, const std::string& mid, int mlineindex, const std::string& sdp);
    void onAddRemoteStream(wrtc::Peer* conn, webrtc::MediaStreamInterface* stream);
    void onRemoveRemoteStream(wrtc::Peer* conn, webrtc::MediaStreamInterface* stream);
    void onStable(wrtc::Peer* conn);
    void onClosed(wrtc::Peer* conn);
    void onFailure(wrtc::Peer* conn, const std::string& error);

    void postMessage(const smpl::Message& m);
    void syncMessage(const ipc::Action& action);

    void onPeerConnected(smpl::Peer& peer);
    void onPeerMessage(smpl::Message& m);
    void onPeerDiconnected(const smpl::Peer& peer);

    void onClientStateChange(void* sender, sockio::ClientState& state, const sockio::ClientState& oldState);

	

protected:
    ipc::SyncQueue<> _ipc;
#if USE_SSL
    smpl::SSLClient _client;
#else
    smpl::TCPClient _client;
#endif
    std::unique_ptr<CvStreamRecorder> _recorder;
	wrtc::PeerFactoryContext _context;
};


} // namespace scy


#endif
