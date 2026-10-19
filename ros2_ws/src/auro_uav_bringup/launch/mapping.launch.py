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
