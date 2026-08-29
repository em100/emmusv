
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='auroadas',
            executable='auroadas_node',
            name='auroadas_node',
            output='screen',
            parameters=[
                'config/camera.yaml',
                'config/imu.yaml',
                'config/gps.yaml',
                'config/system.yaml'
            ]
        )
    ])

Node(
    package='rviz2',
    executable='rviz2',
    name='rviz2',
    output='screen',
    arguments=['-d', 'config/rviz_config.rviz']
)
