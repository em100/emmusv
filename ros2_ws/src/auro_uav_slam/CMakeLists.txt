cmake_minimum_required(VERSION 3.8)
project(auro_uav_slam)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#########################################################
# Dependencies
#########################################################

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

#########################################################
# SLAM Nodes
#########################################################

add_executable(
  feature_tracker
  src/feature_tracker.cpp
)

ament_target_dependencies(
  feature_tracker
  rclcpp
)

add_executable(
  visual_odometry
  src/visual_odometry.cpp
)

ament_target_dependencies(
  visual_odometry
  rclcpp
)

add_executable(
  loop_closure
  src/loop_closure.cpp
)

ament_target_dependencies(
  loop_closure
  rclcpp
)

add_executable(
  pose_graph
  src/pose_graph.cpp
)

ament_target_dependencies(
  pose_graph
  rclcpp
)

add_executable(
  localization
  src/localization.cpp
)

ament_target_dependencies(
  localization
  rclcpp
)

#########################################################
# Install Nodes
#########################################################

install(
  TARGETS
    feature_tracker
    visual_odometry
    loop_closure
    pose_graph
    localization
  DESTINATION lib/${PROJECT_NAME}
)

#########################################################
# Install Launch Files
#########################################################

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

#########################################################
# Install Config Files
#########################################################

install(
  DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)

#########################################################

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)

  ament_lint_auto_find_test_dependencies()
endif()

#########################################################

ament_package()