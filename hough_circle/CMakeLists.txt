project(HOUGH_CIRCLE)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

find_package(OpenCV REQUIRED)

#vision executable
add_executable (hough_circle HoughCircle_Demo.cpp)
target_link_libraries(hough_circle ${OpenCV_LIBS})
