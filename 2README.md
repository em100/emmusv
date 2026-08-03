# AURORA‑ADAS

AURORA‑ADAS is a modular autonomy architecture for aerial robots integrating:

- GPU‑accelerated perception (DroNet, depth, semantic segmentation, ViT)
- Visual‑inertial odometry and factor‑graph SLAM
- Latent world‑modeling and risk prediction
- Semantic + geometric mapping
- Global and local planning (A*/D*, MPC, RL prior)
- Safety supervision and emergency overrides
- PX4 offboard control via MAVLink

## Features

- Real‑time deployment on NVIDIA Jetson (TensorRT FP16/INT8)
- ROS2‑based modular architecture
- AirSim and PX4 SITL simulation workflows
- Semantic‑aware mapping and planning
- Predictive world‑model for safety‑aware navigation

## Architecture

```text
RGB → DroNet → Steering + Collision → Safety + MPC
RGB → Depth → Local Mapper → Planning
RGB → SemSeg → Global Mapper → Planning
RGB → ViT → Latent → Dynamics → Risk → Safety
IMU + VIO + SLAM → EKF → Pose → Mapping + Planning
Planning → Trajectory → PX4 Controller → MAVLink → PX4
