#!/usr/bin/env python3
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    dronet_node = Node(
        package='dronet_perception',
        executable='dronet_node',
        name='dronet_node',
        output='screen',
        parameters=[{
            'engine_path': '/home/ubuntu/aurora_ws/src/AURORA-ADAS/perception/dronet_perception/models/dronet_fp16.engine',
            'input_topic': '/camera/front/image_raw'
        }]
    )

    controller_node = Node(
        package='px4_interface',
        executable='px4_controller',
        name='px4_controller',
        output='screen',
        parameters=[{
            'max_forward_speed': 1.0,
            'max_yaw_rate': 1.2,
            'collision_stop_threshold': 0.9
        }]
    )

    return LaunchDescription([
        dronet_node,
        controller_node
    ])

