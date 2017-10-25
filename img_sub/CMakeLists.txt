project(img_sub)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

find_package(OpenCV REQUIRED)

#vision executable
add_executable (img_sub img_sub.cpp)
target_link_libraries(img_sub ${OpenCV_LIBS})
