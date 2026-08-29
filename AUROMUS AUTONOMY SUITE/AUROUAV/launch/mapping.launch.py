#!/usr/bin/env python3
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    local_mapper = Node(
        package='local_mapper',
        executable='local_mapper_node',
        name='local_mapper',
        output='screen'
    )

    global_mapper = Node(
        package='global_mapper',
        executable='global_mapper_node',
        name='global_mapper',
        output='screen'
    )

    return LaunchDescription([
        local_mapper,
        global_mapper
    ])
