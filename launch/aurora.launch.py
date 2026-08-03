#!/usr/bin/env python3
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import GroupAction, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import SetRemap

def generate_launch_description():

    # -----------------------------
    # Perception: DroNet + Depth + SemSeg
    # -----------------------------
    dronet_node = Node(
        package='dronet_perception',
        executable='dronet_node',
        name='dronet_node',
        output='screen',
        parameters=[{
            'engine_path': '/home/ubuntu/aurora_ws/src/AURORA-ADAS/perception/dronet_perception/models/dronet_fp16.engine',
            'input_topic': '/camera/front/image_raw'
        }]
    )

    depth_node = Node(
        package='depth_estimator',
        executable='depth_node',
        name='depth_node',
        output='screen'
    )

    semseg_node = Node(
        package='semantic_segmentation',
        executable='semseg_node',
        name='semantic_segmentation',
        output='screen'
    )

    # -----------------------------
    # World Model (ViT + Latent Dynamics)
    # -----------------------------
    world_model_node = Node(
        package='world_model_node',
        executable='world_model_node',
        name='world_model_node',
        output='screen'
    )

    # -----------------------------
    # Estimation: VIO + EKF + SLAM
    # -----------------------------
    vio_node = Node(
        package='vio_frontend',
        executable='vio_node',
        name='vio_node',
        output='screen'
    )

    ekf_node = Node(
        package='fusion_ekf',
        executable='ekf_fusion_node',
        name='ekf_fusion',
        output='screen'
    )

    slam_node = Node(
        package='slam_backend_gtsam',
        executable='slam_node',
        name='slam_node',
        output='screen'
    )

    # -----------------------------
    # Mapping: Local + Global
    # -----------------------------
    local_mapper = Node(
        package='local_mapper',
        executable='local_mapper_node',
        name='local_mapper',
        output='screen'
    )

    global_mapper = Node(
        package='global_mapper',
        executable='global_mapper_node',
        name='global_mapper',
        output='screen'
    )

    # -----------------------------
    # Planning: Global + Local MPC
    # -----------------------------
    global_planner = Node(
        package='global_planner',
        executable='global_planner_node',
        name='global_planner',
        output='screen'
    )

    local_planner = Node(
        package='local_planner',
        executable='local_planner_node',
        name='local_planner',
        output='screen'
    )

    # -----------------------------
    # Safety Supervisor
    # -----------------------------
    safety_node = Node(
        package='safety_monitor',
        executable='safety_node',
        name='safety_monitor',
        output='screen'
    )

    # -----------------------------
    # PX4 Interface (MAVLink Offboard)
    # -----------------------------
    px4_interface = Node(
        package='px4_interface',
        executable='px4_controller',
        name='px4_controller',
        output='screen'
    )

    # -----------------------------
    # Group all nodes
    # -----------------------------
    aurora_group = GroupAction([
        dronet_node,
        depth_node,
        semseg_node,
        world_model_node,
        vio_node,
        ekf_node,
        slam_node,
        local_mapper,
        global_mapper,
        global_planner,
        local_planner,
        safety_node,
        px4_interface
    ])

    return LaunchDescription([aurora_group])
