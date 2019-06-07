cmake_minimum_required(VERSION 3.13)
project(LivenessVerification)

set(CMAKE_CXX_STANDARD 14)

add_executable(testMain testMain.cpp)
target_link_libraries(testMain /usr/lib/x86_64-linux-gnu/libbdd.so.0)