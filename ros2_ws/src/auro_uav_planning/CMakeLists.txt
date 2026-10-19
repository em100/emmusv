cmake_minimum_required(VERSION 3.8)
project(auro_uav_planning)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

#########################################################

add_executable(
  global_planner
  src/global_planner.cpp
)

ament_target_dependencies(
  global_planner
  rclcpp
)

#########################################################

add_executable(
  local_planner
  src/local_planner.cpp
)

ament_target_dependencies(
  local_planner
  rclcpp
)

#########################################################

add_executable(
  mpc_controller
  src/mpc_controller.cpp
)

ament_target_dependencies(
  mpc_controller
  rclcpp
)

#########################################################

install(
  TARGETS
    global_planner
    local_planner
    mpc_controller
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