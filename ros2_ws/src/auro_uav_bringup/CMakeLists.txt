cmake_minimum_required(VERSION 3.8)
project(auro_uav_bringup)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#########################################################
# Dependencies
#########################################################

find_package(ament_cmake REQUIRED)

#########################################################
# Install Launch Files
#########################################################

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

#########################################################
# Install Config Files (optional)
#########################################################

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/config")
  install(
    DIRECTORY config
    DESTINATION share/${PROJECT_NAME}
  )
endif()

#########################################################

ament_package()