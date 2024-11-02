cmake_minimum_required(VERSION 3.28)
project(fcitx5_detector)

set(CMAKE_CXX_STANDARD 17)
find_package(JNI REQUIRED)

find_package(sdbus-c++ REQUIRED)

add_library(fcitx5_detector SHARED main.cpp)

target_link_libraries(fcitx5_detector PRIVATE SDBusCpp::sdbus-c++)
include_directories(${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2})