from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    return LaunchDescription([

        # Perception
        Node(
            package='auro_uav_perception',
            executable='dronet_node',
            name='dronet'
        ),
        Node(
            package='auro_uav_perception',
            executable='depth_node',
            name='depth_estimator'
        ),
        Node(
            package='auro_uav_perception',
            executable='semseg_node',
            name='semantic_segmentation'
        ),
        Node(
            package='auro_uav_perception',
            executable='vit_detr_node',
            name='vit_detr'
        ),

        # SLAM
        Node(
            package='auro_uav_slam',
            executable='vio_node',
            name='vio'
        ),

        # Mapping
        Node(
            package='auro_uav_mapping',
            executable='local_map_node',
            name='local_map'
        ),
        Node(
            package='auro_uav_mapping',
            executable='global_map_node',
            name='global_map'
        ),

        # Planning + Control
        Node(
            package='auro_uav_control',
            executable='mpc_node',
            name='mpc'
        ),
        Node(
            package='auro_uav_control',
            executable='rl_prior_node',
            name='rl_prior'
        ),
        Node(
            package='auro_uav_control',
            executable='px4_bridge_node',
            name='px4_bridge'
        ),

        # Safety
        Node(
            package='auro_uav_safety',
            executable='safety_supervisor',
            name='safety_supervisor'
        )
    ])
