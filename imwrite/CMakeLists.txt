project(imwrite)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

find_package(OpenCV REQUIRED)

#vision executable
add_executable (imwrite imwrite.cpp)
target_link_libraries(imwrite ${OpenCV_LIBS})
