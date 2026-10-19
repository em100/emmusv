#!/usr/bin/env python3
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    safety_monitor = Node(
        package='safety_monitor',
        executable='safety_node',
        name='safety_monitor',
        output='screen',
        parameters=[{
            'collision_stop_threshold': 0.9,
            'slam_low_confidence_threshold': 0.3,
            'emergency_land_risk': 0.8
        }]
    )

    rule_engine = Node(
        package='rule_engine',
        executable='rule_engine_node',
        name='rule_engine',
        output='screen'
    )

    emergency_handler = Node(
        package='safety_monitor',
        executable='emergency_handler',
        name='emergency_handler',
        output='screen'
    )

    return LaunchDescription([
        safety_monitor,
        rule_engine,
        emergency_handler
    ])
