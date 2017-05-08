documentation:

cmake-gui

where is the source code:
E:/Dev/webrtc/webrtc-mentor-client

where to build the binaries:
E:/Dev/webrtc/webrtc-mentor-client/build

press Configure

create "build" directory if it doesn't exist

specify generator: Visual Studio 14 2015 Win64

If error about LibSourcey not found:
- manually set LibSourcey_ROOT_DIR (e.g. "E:/libsourcey/002/libsourcey")
- also set LibSourcey_INSTALL_DIR

If error about OpenCV not found:
- manually set OpenCV_DIR (e.g. "E:/Libs/opencv320/opencv/build")



- set FFmpeg_DIR (e.g. "E:/Libs/ffmpeg-20170225-7e4f32f-win64-dev")


WEBRTC_ROOT_DIR: E:/webrtc/004/webrtc-checkout/src

Building libsourcey

cmake -G "Visual Studio 14 Win64" .. -DCMAKE_BUILD_TYPE=DEBUG -DBUILD_SHARED_LIBS=OFF -DBUILD_MODULES=OFF -DBUILD_APPLICATIONS=ON -DBUILD_SAMPLES=OFF -DBUILD_TESTS=OFF -DWITH_WEBRTC=ON -DWITH_OPENCV=OFF -DWITH_FFMPEG=ON -DBUILD_MODULE_base=ON -DBUILD_MODULE_crypto=ON -DBUILD_MODULE_http=ON -DBUILD_MODULE_json=ON -DBUILD_MODULE_av=ON -DBUILD_MODULE_net=ON -DBUILD_MODULE_socketio=ON -DBUILD_MODULE_symple=ON -DBUILD_MODULE_util=ON -DBUILD_MODULE_uv=ON -DBUILD_MODULE_stun=ON -DBUILD_MODULE_turn=ON -DBUILD_MODULE_webrtc=ON -DOPENSSL_ROOT_DIR=C:/OpenSSL-Win64 -DFFMPEG_ROOT_DIR=E:/Libs/ffmpeg-20170225-7e4f32f-win64-dev -DWEBRTC_ROOT_DIR=E:/Dev/webrtc/webrtc-mentor-client/webrtc-checkout-src -DCMAKE_INSTALL_PREFIX=..