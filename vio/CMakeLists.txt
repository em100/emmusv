cmake_minimum_required(VERSION 3.16)

project(auro_uav_vio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

add_library(
    visual_odometry
    visual_odometry/visual_odometry.cpp
)

add_library(
    imu_preintegration
    imu_preintegration/imu_preintegration.cpp
)

target_link_libraries(
    visual_odometry
    ${OpenCV_LIBS}
)

target_link_libraries(
    imu_preintegration
    Eigen3::Eigen
)