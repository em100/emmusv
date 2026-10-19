cmake_minimum_required(VERSION 3.8)
project(auro_uav_perception)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

#
# DroNet Node
#
add_executable(
  dronet_node
  src/dronet_node.cpp
)

ament_target_dependencies(
  dronet_node
  rclcpp
)

#
# Future Nodes
#
 add_executable(depth_node src/depth_node.cpp)
 ament_target_dependencies(depth_node rclcpp)

 add_executable(semseg_node src/semseg_node.cpp)
 ament_target_dependencies(semseg_node rclcpp)

 add_executable(vit_detr_node src/vit_detr_node.cpp)
 ament_target_dependencies(vit_detr_node rclcpp)

install(
  TARGETS
    dronet_node
    depth_node
    semseg_node
    vit_detr_node
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
