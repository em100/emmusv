from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    return LaunchDescription([

        Node(
            package='auro_uav_control',
            executable='px4_bridge',
            output='screen'),

        Node(
            package='auro_uav_control',
            executable='offboard_manager',
            output='screen'),

        Node(
            package='auro_uav_control',
            executable='controller',
            output='screen')
    ])
