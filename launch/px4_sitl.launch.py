#!/usr/bin/env python3
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, GroupAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
import os

def generate_launch_description():

    px4_sitl = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                os.getenv('PX4_SITL_PATH', '/usr/share/px4'),
                'launch',
                'px4_sitl.launch.py'
            )
        )
    )

    mavros = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                '/opt/ros/humble/share/mavros/launch',
                'px4.launch.py'
            )
        ),
        launch_arguments={'fcu_url': 'udp://:14540@'}.items()
    )

    aurora_stack = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                os.getenv('AURORA_WS', '/home/ubuntu/aurora_ws'),
                'src/AURORA-ADAS/launch',
                'aurora.launch.py'
            )
        )
    )

    return LaunchDescription([
        px4_sitl,
        mavros,
        aurora_stack
    ])
