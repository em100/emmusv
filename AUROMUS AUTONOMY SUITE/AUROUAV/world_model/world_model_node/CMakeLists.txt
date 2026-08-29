cmake_minimum_required(VERSION 3.5)
project(world_model_node)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(cv_bridge REQUIRED)

include_directories(include)

add_executable(world_model_node src/world_model_node.cpp)
ament_target_dependencies(world_model_node
  rclcpp sensor_msgs geometry_msgs cv_bridge
)

install(TARGETS world_model_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/
  DESTINATION include/)

ament_package()
