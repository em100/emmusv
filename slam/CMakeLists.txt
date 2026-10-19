cmake_minimum_required(VERSION 3.16)

project(auro_uav_slam)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

add_library(
    feature_tracker
    feature_tracking/feature_tracker.cpp
)

add_library(
    loop_closure
    loop_closure/loop_closure.cpp
)

add_library(
    localization
    localization/localization.cpp
)

target_link_libraries(
    feature_tracker
    ${OpenCV_LIBS}
)

target_link_libraries(
    loop_closure
    ${OpenCV_LIBS}
)

target_link_libraries(
    localization
    Eigen3::Eigen
)