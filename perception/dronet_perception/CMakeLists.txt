cmake_minimum_required(VERSION 3.5)
project(dronet_perception)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(geometry_msgs REQUIRED)

include_directories(include)

add_message_files(
  FILES
  DronetCommand.msg
)

generate_messages(
  DEPENDENCIES std_msgs
)

add_executable(dronet_node src/dronet_node.cpp src/inference_engine.cpp)
ament_target_dependencies(dronet_node
  rclcpp sensor_msgs cv_bridge OpenCV geometry_msgs
)

install(TARGETS dronet_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/
  DESTINATION include/)

install(DIRECTORY models/
  DESTINATION share/${PROJECT_NAME}/models)

ament_package()
