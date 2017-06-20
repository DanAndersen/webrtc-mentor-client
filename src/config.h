#ifndef SCY_WebRTC_WebRTCRecorder_Config_H
#define SCY_WebRTC_WebRTCRecorder_Config_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include "scy/base.h"
#include "scy/av/codec.h"
#include "scy/av/format.h"


//#define SERVER_HOST "localhost"
#define SERVER_HOST "andersed-webrtc-signal-server.herokuapp.com"
#define USE_SSL 1 // 1
#if USE_SSL
#define SERVER_PORT 443
#else
#define SERVER_PORT 4500
#endif

#define OUTPUT_WIDTH 640
#define OUTPUT_HEIGHT 480

#endif
