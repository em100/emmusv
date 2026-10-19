cmake_minimum_required(VERSION 3.5)
project(global_mapper)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(include)

add_executable(global_mapper_node src/global_mapper_node.cpp)
ament_target_dependencies(global_mapper_node
  rclcpp sensor_msgs nav_msgs cv_bridge OpenCV
)

install(TARGETS global_mapper_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/
  DESTINATION include/)

ament_package()
