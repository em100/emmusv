cmake_minimum_required(VERSION 3.8)
project(auro_uav_safety)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(
  risk_fusion
  src/risk_fusion.cpp
)

ament_target_dependencies(
  risk_fusion
  rclcpp
)

add_executable(
  safety_supervisor
  src/safety_supervisor.cpp
)

ament_target_dependencies(
  safety_supervisor
  rclcpp
)

add_executable(
  emergency_handler
  src/emergency_handler.cpp
)

ament_target_dependencies(
  emergency_handler
  rclcpp
)

install(
  TARGETS
    risk_fusion
    safety_supervisor
    emergency_handler
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