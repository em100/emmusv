cmake_minimum_required(VERSION 3.8)
project(auro_uav_world_model)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#########################################################
# Dependencies
#########################################################

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

#########################################################
# ViT Encoder
#########################################################

add_executable(
  vit_encoder
  src/vit_encoder.cpp
)

ament_target_dependencies(
  vit_encoder
  rclcpp
)

#########################################################
# Latent Dynamics
#########################################################

add_executable(
  latent_dynamics
  src/latent_dynamics.cpp
)

ament_target_dependencies(
  latent_dynamics
  rclcpp
)

#########################################################
# Risk Decoder
#########################################################

add_executable(
  risk_decoder
  src/risk_decoder.cpp
)

ament_target_dependencies(
  risk_decoder
  rclcpp
)

#########################################################
# Free Space Predictor
#########################################################

add_executable(
  free_space_predictor
  src/free_space_predictor.cpp
)

ament_target_dependencies(
  free_space_predictor
  rclcpp
)

#########################################################
# Install Executables
#########################################################

install(
  TARGETS
    vit_encoder
    latent_dynamics
    risk_decoder
    free_space_predictor
  DESTINATION lib/${PROJECT_NAME}
)

#########################################################
# Launch Files
#########################################################

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

#########################################################
# Config Files
#########################################################

install(
  DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)

#########################################################

ament_package()