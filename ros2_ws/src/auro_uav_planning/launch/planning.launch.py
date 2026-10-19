from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    return LaunchDescription([

        Node(
            package='auro_uav_planning',
            executable='global_planner',
            output='screen'),

        Node(
            package='auro_uav_planning',
            executable='local_planner',
            output='screen'),

        Node(
            package='auro_uav_planning',
            executable='mpc_controller',
            output='screen')
    ])