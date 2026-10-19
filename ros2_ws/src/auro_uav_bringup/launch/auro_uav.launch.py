from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    pkg = get_package_share_directory('auro_uav_bringup')

    launches = [
        'perception.launch.py',
        'slam.launch.py',
        'mapping.launch.py',
        'planning.launch.py',
        'control.launch.py',
        'safety.launch.py',
        'world_model.launch.py'
    ]

    return LaunchDescription([
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join(pkg, 'launch', launch_file)
            )
        )
        for launch_file in launches
    ])
