cmake_minimum_required(VERSION 3.8)
project(auro_uav_control)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

#########################################################

add_executable(
  px4_bridge
  src/px4_bridge.cpp
)

ament_target_dependencies(
  px4_bridge
  rclcpp
)

#########################################################

add_executable(
  offboard_manager
  src/offboard_manager.cpp
)

ament_target_dependencies(
  offboard_manager
  rclcpp
)

#########################################################

add_executable(
  controller
  src/controller.cpp
)

ament_target_dependencies(
  controller
  rclcpp
)

#########################################################

install(
  TARGETS
    px4_bridge
    offboard_manager
    controller
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

install(
  DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()