cmake_minimum_required (VERSION 2.8.10)
project(WebRTCMentorClient)

set(sourcedir ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(sourcefiles ${sourcedir}/*.cpp)
set(headerfiles ${sourcedir}/*.h ${sourcedir}/*.hpp)

set(OpenCV_DIR "D:/Dev/holowebrtc/opencv/build")
message("Finding OpenCV...")
find_package( OpenCV REQUIRED ) # May need to override OpenCV_DIR (e.g "E:/Libs/opencv320/opencv/build")

# include LibSourcey

# LibSourcey-specific flags
set(CMAKE_BUILD_TYPE DEBUG )
set(BUILD_SHARED_LIBS OFF )
set(BUILD_MODULES OFF )
set(BUILD_APPLICATIONS ON )
set(BUILD_SAMPLES OFF )
set(BUILD_TESTS OFF )
set(WITH_WEBRTC ON )
set(WITH_OPENCV OFF ) # we don't build LibSourcey with OpenCV, but we use it in our own codebase
set(WITH_FFMPEG ON )
set(BUILD_MODULE_base ON )
set(BUILD_MODULE_crypto ON )
set(BUILD_MODULE_http ON )
set(BUILD_MODULE_json ON )
set(BUILD_MODULE_av ON )
set(BUILD_MODULE_net ON )
set(BUILD_MODULE_socketio ON )
set(BUILD_MODULE_symple ON )
set(BUILD_MODULE_util ON )
set(BUILD_MODULE_uv ON )
set(BUILD_MODULE_stun ON )
set(BUILD_MODULE_turn ON )
set(BUILD_MODULE_webrtc ON )
set(OPENSSL_ROOT_DIR "C:/OpenSSL-Win64")
set(FFMPEG_ROOT_DIR "D:/Dev/holowebrtc/ffmpeg-3.3.1-win64")
set(WEBRTC_ROOT_DIR "D:/Dev/holowebrtc/webrtc")

set(LibSourcey_DIR "D:/Dev/holowebrtc/libsourcey")
include("${LibSourcey_DIR}/LibSourcey.cmake")

#link_libraries(${LibSourcey_LIBRARIES} ${FFmpeg_LIBRARIES} ${OpenCV_LIBS})

# Header file directories of dependency libraries
include_directories(
  # OpenCV
  ${OpenCV_INCLUDE_DIRS}
  # LibSourcey
  ${LibSourcey_INCLUDE_DIRS}
  # Resource file
  ${CMAKE_CURRENT_BINARY_DIR}
)

#add_definitions(-DNOMINMAX) # to prevent an error with std::min ( http://stackoverflow.com/questions/5004858/stdmin-gives-error )

file(GLOB extra_webrtc_libs "${WEBRTC_ROOT_DIR}/out/Debug/*.lib")
message("extra_webrtc_libs: " "${extra_webrtc_libs}")
list(REMOVE_ITEM extra_webrtc_libs "${WEBRTC_ROOT_DIR}/out/Debug/protobuf_full.lib")

file(GLOB_RECURSE sources ${sourcefiles})
file(GLOB_RECURSE headers ${headerfiles})

add_executable(WebRTCMentorClient ${sources} ${headers})

target_link_libraries(WebRTCMentorClient ${LibSourcey_LIBRARIES} ${FFmpeg_LIBRARIES} ${OpenCV_LIBS} ${WEBRTC_LIBRARIES} ${extra_webrtc_libs})

set_default_project_dependencies(WebRTCMentorClient base crypto av net http util json socketio symple webrtc)

set_target_properties(WebRTCMentorClient PROPERTIES OUTPUT_NAME "WebRTCMentorClient")

message( "LibSourcey_INCLUDE_DIRS: " "${LibSourcey_INCLUDE_DIRS}")
message( "FFmpeg_LIBRARIES: " "${FFmpeg_LIBRARIES}")
message( "WEBRTC_LIBRARIES: " "${WEBRTC_LIBRARIES}")


install(TARGETS WebRTCMentorClient RUNTIME DESTINATION bin)