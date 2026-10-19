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
