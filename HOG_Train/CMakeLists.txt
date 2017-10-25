project(HOG_Train)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

find_package(OpenCV REQUIRED)

#vision executable
add_executable (HOG_Train HOG_Train.cpp )
target_link_libraries(HOG_Train ${OpenCV_LIBS})
