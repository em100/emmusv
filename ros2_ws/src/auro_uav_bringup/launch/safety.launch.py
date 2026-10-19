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
