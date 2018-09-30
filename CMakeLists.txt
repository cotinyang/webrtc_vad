CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
PROJECT(webrtc_vad)

SET(CMAKE_CXX_STANDARD 11)
ADD_DEFINITIONS(-g)


SET(WEBRTC_SOURCE_DIR ${PROJECT_SOURCE_DIR}/webrtc)
SET(VAD_SOURCE_DIR ${WEBRTC_SOURCE_DIR}/common_audio/vad)
SET(SIGNAL_SOURCE_DIR ${WEBRTC_SOURCE_DIR}/common_audio/signal_processing)
SET(RTC_BASE_SOURCE_DIR ${WEBRTC_SOURCE_DIR}/rtc_base)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/webrtc_vad)
SET(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/lib)
SET(HEADER_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/include)

ADD_CUSTOM_TARGET(copy_header ALL
    COMMAND
    ${CMAKE_COMMAND} -E make_directory ${HEADER_OUTPUT_PATH}
    COMMAND
    ${CMAKE_COMMAND} -E copy_directory ${VAD_SOURCE_DIR}/include ${HEADER_OUTPUT_PATH}
)

FILE(GLOB VAD_SOURCE_FILES
    ${VAD_SOURCE_DIR}/vad_core.c
    ${VAD_SOURCE_DIR}/vad_filterbank.c
    ${VAD_SOURCE_DIR}/vad_gmm.c
    ${VAD_SOURCE_DIR}/vad_sp.c
    ${VAD_SOURCE_DIR}/vad.cc
    ${VAD_SOURCE_DIR}/webrtc_vad.c
    ${SIGNAL_SOURCE_DIR}/energy.c
    ${SIGNAL_SOURCE_DIR}/resample_48khz.c
    ${SIGNAL_SOURCE_DIR}/resample_fractional.c
    ${SIGNAL_SOURCE_DIR}/resample_by_2_internal.c
    ${SIGNAL_SOURCE_DIR}/spl_init.c
    ${SIGNAL_SOURCE_DIR}/min_max_operations.c
    ${SIGNAL_SOURCE_DIR}/downsample_fast.c
    ${SIGNAL_SOURCE_DIR}/get_scaling_square.c
    ${SIGNAL_SOURCE_DIR}/vector_scaling_operations.c
    ${SIGNAL_SOURCE_DIR}/division_operations.c
    ${SIGNAL_SOURCE_DIR}/cross_correlation.c
    ${RTC_BASE_SOURCE_DIR}/checks.cc
)

INCLUDE_DIRECTORIES(
    ${WEBRTC_SOURCE_DIR}
)

ADD_DEFINITIONS(
    -DWEBRTC_LINUX
    -DWEBRTC_POSIX
)
ADD_LIBRARY(webrtc_vad SHARED ${VAD_SOURCE_FILES})
TARGET_LINK_LIBRARIES(webrtc_vad pthread)
ADD_DEPENDENCIES(webrtc_vad copy_header)

INCLUDE_DIRECTORIES(
    ${HEADER_OUTPUT_PATH}
)

LINK_DIRECTORIES(
    ${LIBRARY_OUTPUT_PATH}
)

ADD_EXECUTABLE(test main.c)
TARGET_LINK_LIBRARIES(test webrtc_vad)
