cmake_minimum_required(VERSION 3.8)
project(auro_uav_mapping)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

#########################################################
# Occupancy Grid
#########################################################

add_executable(
  occupancy_grid_node
  src/occupancy_grid_node.cpp
)

ament_target_dependencies(
  occupancy_grid_node
  rclcpp
)

#########################################################
# Point Cloud Mapping
#########################################################

add_executable(
  pointcloud_mapping_node
  src/pointcloud_mapping_node.cpp
)

ament_target_dependencies(
  pointcloud_mapping_node
  rclcpp
)

#########################################################
# Semantic Mapping
#########################################################

add_executable(
  semantic_mapping_node
  src/semantic_mapping_node.cpp
)

ament_target_dependencies(
  semantic_mapping_node
  rclcpp
)

#########################################################

install(
  TARGETS
    occupancy_grid_node
    pointcloud_mapping_node
    semantic_mapping_node
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