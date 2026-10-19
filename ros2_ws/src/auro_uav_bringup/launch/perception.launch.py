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
