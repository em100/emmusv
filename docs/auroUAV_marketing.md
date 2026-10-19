#⭐ 5. Marketing One‑Pager for AUROUAV


AUROUAV — Unified Autonomy Architecture for GNSS‑Denied UAV Navigation
Overview
AUROUAV is a modular autonomy stack designed for UAVs operating in GNSS‑denied environments. It integrates transformer‑based perception, visual‑inertial SLAM, semantic mapping, MPC trajectory optimization, and reinforcement‑learning‑conditioned steering priors into a single deployable system.

Key Capabilities
Transformer Perception  
ViT‑DETR, semantic segmentation, depth estimation

Reactive Control  
DroNet steering + collision prediction

Predictive World Model  
ViT encoder + latent dynamics

Multi‑Layer Mapping  
Local occupancy + global semantic voxel map

Hierarchical Planning  
A* global planner + MPC local controller

Safety Supervision  
Risk fusion + emergency overrides

PX4 Integration  
MAVLink offboard control

Jetson Optimization  
TensorRT FP16/INT8 acceleration

Applications
Search & rescue

Indoor navigation

Tunnel inspection

Forest flight

Disaster response

Platforms
Jetson Orin

Jetson Xavier

Jetson Nano

PX4‑based UAVs

Simulation Pipeline
AirSim → PX4 SITL → Gazebo → AUROUAV evaluation

Get Started
GitHub: https://github.com/em100/emmusv  
Documentation: /docs/  
Diagrams: /docs/diagrams/