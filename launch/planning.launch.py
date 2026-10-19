#!/usr/bin/env python3
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    global_planner = Node(
        package='global_planner',
        executable='global_planner_node',
        name='global_planner',
        output='screen',
        parameters=[{
            'algorithm': 'A*',
            'inflation_radius': 0.5
        }]
    )

    local_planner = Node(
        package='local_planner',
        executable='local_planner_node',
        name='local_planner',
        output='screen',
        parameters=[{
            'mpc_horizon': 15,
            'mpc_dt': 0.1,
            'risk_weight': 0.4,
            'steering_prior_weight': 0.3
        }]
    )

    trajectory_pub = Node(
        package='local_planner',
        executable='trajectory_publisher',
        name='trajectory_publisher',
        output='screen'
    )

    return LaunchDescription([
        global_planner,
        local_planner,
        trajectory_pub
    ])
