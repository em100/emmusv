cmake_minimum_required(VERSION 3.8)
project(auro_uav_msgs)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#########################################################
# Dependencies
#########################################################

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

#########################################################
# Message Generation
#########################################################

rosidl_generate_interfaces(${PROJECT_NAME}

  "msg/ControlCmd.msg"
  "msg/RiskScore.msg"
  "msg/WorldModelState.msg"
  "msg/SemanticVoxel.msg"
  "msg/VoxelMap.msg"
  "msg/Trajectory.msg"

  DEPENDENCIES
    std_msgs
    geometry_msgs
)

#########################################################

ament_export_dependencies(
  rosidl_default_runtime
)

#########################################################

ament_package()
