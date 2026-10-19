cmake_minimum_required(VERSION 3.5)
project(local_mapper)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)

include_directories(include)

add_executable(local_mapper_node src/local_mapper_node.cpp)
ament_target_dependencies(local_mapper_node
  rclcpp sensor_msgs nav_msgs tf2 tf2_ros
)

install(TARGETS local_mapper_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/
  DESTINATION include/)

ament_package()
