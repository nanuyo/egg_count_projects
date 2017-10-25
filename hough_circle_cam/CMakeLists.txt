project(HOUGH_CIRCLE_CAM)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

find_package(OpenCV REQUIRED)

#vision executable
add_executable (hough_circle_cam HoughCircle_Cam.cpp)
target_link_libraries(hough_circle_cam ${OpenCV_LIBS})
