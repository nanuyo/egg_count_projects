project(TEST)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

find_package(OpenCV REQUIRED)

#vision executable
add_executable (test test.cpp)
target_link_libraries(test ${OpenCV_LIBS})
