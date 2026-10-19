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
