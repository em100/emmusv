#!/usr/bin/env python3
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    vit_encoder = Node(
        package='world_model_node',
        executable='vit_encoder_node',
        name='vit_encoder',
        output='screen',
        parameters=[{
            'vit_config': 'world_model/vit_encoder/vit_config.json',
            'input_topic': '/camera/front/image_raw'
        }]
    )

    latent_dynamics = Node(
        package='world_model_node',
        executable='latent_dynamics_node',
        name='latent_dynamics',
        output='screen',
        parameters=[{
            'latent_dim': 256,
            'prediction_horizon': 10
        }]
    )

    free_space_predictor = Node(
        package='world_model_node',
        executable='free_space_node',
        name='free_space_predictor',
        output='screen'
    )

    risk_predictor = Node(
        package='world_model_node',
        executable='risk_predictor_node',
        name='risk_predictor',
        output='screen'
    )

    steering_enhancer = Node(
        package='world_model_node',
        executable='steering_enhancer_node',
        name='steering_enhancer',
        output='screen'
    )

    return LaunchDescription([
        vit_encoder,
        latent_dynamics,
        free_space_predictor,
        risk_predictor,
        steering_enhancer
    ])
