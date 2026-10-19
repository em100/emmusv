from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    return LaunchDescription([

        Node(
            package='auro_uav_slam',
            executable='feature_tracker',
            name='feature_tracker',
            output='screen'
        ),

        Node(
            package='auro_uav_slam',
            executable='visual_odometry',
            name='visual_odometry',
            output='screen'
        ),

        Node(
            package='auro_uav_slam',
            executable='loop_closure',
            name='loop_closure',
            output='screen'
        ),

        Node(
            package='auro_uav_slam',
            executable='pose_graph',
            name='pose_graph',
            output='screen'
        ),

        Node(
            package='auro_uav_slam',
            executable='localization',
            name='localization',
            output='screen'
        )

    ])
