project(absdiff)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

find_package(OpenCV REQUIRED)

#vision executable
add_executable (absdiff absdiff.cpp)
target_link_libraries(absdiff ${OpenCV_LIBS})
