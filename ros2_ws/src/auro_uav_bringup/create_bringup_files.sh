#!/usr/bin/env bash

mkdir -p launch

##################################################
# Perception
##################################################

cat > launch/perception.launch.py << 'EOF'
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([

        Node(
            package='auro_uav_perception',
            executable='dronet_node',
            output='screen'),

        Node(
            package='auro_uav_perception',
            executable='depth_node',
            output='screen'),

        Node(
            package='auro_uav_perception',
            executable='semseg_node',
            output='screen'),

        Node(
            package='auro_uav_perception',
            executable='vit_detr_node',
            output='screen')
    ])
EOF

##################################################
# SLAM
##################################################

cat > launch/slam.launch.py << 'EOF'
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([

        Node(package='auro_uav_slam',
             executable='feature_tracker',
             output='screen'),

        Node(package='auro_uav_slam',
             executable='visual_odometry',
             output='screen'),

        Node(package='auro_uav_slam',
             executable='loop_closure',
             output='screen'),

        Node(package='auro_uav_slam',
             executable='pose_graph',
             output='screen'),

        Node(package='auro_uav_slam',
             executable='localization',
             output='screen')
    ])
EOF

##################################################
# Mapping
##################################################

cat > launch/mapping.launch.py << 'EOF'
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([

        Node(package='auro_uav_mapping',
             executable='occupancy_grid_node',
             output='screen'),

        Node(package='auro_uav_mapping',
             executable='pointcloud_mapping_node',
             output='screen'),

        Node(package='auro_uav_mapping',
             executable='semantic_mapping_node',
             output='screen')
    ])
EOF

##################################################
# Planning
##################################################

cat > launch/planning.launch.py << 'EOF'
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([

        Node(package='auro_uav_planning',
             executable='global_planner',
             output='screen'),

        Node(package='auro_uav_planning',
             executable='local_planner',
             output='screen'),

        Node(package='auro_uav_planning',
             executable='mpc_controller',
             output='screen')
    ])
EOF

##################################################
# Control
##################################################

cat > launch/control.launch.py << 'EOF'
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([

        Node(package='auro_uav_control',
             executable='px4_bridge',
             output='screen'),

        Node(package='auro_uav_control',
             executable='offboard_manager',
             output='screen'),

        Node(package='auro_uav_control',
             executable='controller',
             output='screen')
    ])
EOF

##################################################
# Safety
##################################################

cat > launch/safety.launch.py << 'EOF'
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([

        Node(package='auro_uav_safety',
             executable='risk_fusion',
             output='screen'),

        Node(package='auro_uav_safety',
             executable='safety_supervisor',
             output='screen'),

        Node(package='auro_uav_safety',
             executable='emergency_handler',
             output='screen')
    ])
EOF

##################################################
# World Model
##################################################

cat > launch/world_model.launch.py << 'EOF'
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([

        Node(package='auro_uav_world_model',
             executable='vit_encoder',
             output='screen'),

        Node(package='auro_uav_world_model',
             executable='latent_dynamics',
             output='screen'),

        Node(package='auro_uav_world_model',
             executable='risk_decoder',
             output='screen'),

        Node(package='auro_uav_world_model',
             executable='free_space_predictor',
             output='screen')
    ])
EOF

##################################################
# Master Launcher
##################################################

cat > launch/auro_uav.launch.py << 'EOF'
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    pkg = get_package_share_directory('auro_uav_bringup')

    launches = [
        'perception.launch.py',
        'slam.launch.py',
        'mapping.launch.py',
        'planning.launch.py',
        'control.launch.py',
        'safety.launch.py',
        'world_model.launch.py'
    ]

    return LaunchDescription([
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join(pkg, 'launch', launch_file)
            )
        )
        for launch_file in launches
    ])
EOF

echo "AUROUAV Bringup launch files created."
