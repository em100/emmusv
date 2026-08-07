# AURORA‑ADAS
Unified Autonomy Architecture for GNSS‑Denied UAV Navigation


🚀 Overview
AURORA‑ADAS is a modular autonomy stack for UAVs, integrating:
GPU‑accelerated perception (DroNet, depth, semantics)
Predictive world‑modeling (ViT + latent dynamics)
Multi‑layer mapping (local + global)
Hierarchical planning (A* + MPC)
Safety supervision (risk fusion + rule engine)
PX4 offboard control (MAVLink bridge + controller)
Simulation‑driven development (AirSim + PX4 SITL)
Designed for Jetson Orin / Xavier / Nano and PX4‑based UAVs.


AURORA‑ADAS integrates transformer‑based perception, visual‑inertial SLAM,
semantic mapping, model predictive control (MPC), and reinforcement learning
(RL) steering priors into a single robust autonomy stack designed for UAVs
operating in GNSS‑denied environments.

## Features
- ViT‑DETR perception pipeline
- Factor‑graph SLAM with IMU + visual factors
- Semantic voxel mapping with Bayesian updates
- MPC trajectory optimization
- RL‑conditioned Gaussian steering prior (PPO/TD3)
- Safety supervisor for collision avoidance

## Architecture Diagram

+---------------------------------------------------------------+
|                        AURORA‑ADAS                            |
+---------------------------------------------------------------+

   +-------------+      +-----------+      +-----------+
   | Perception  | ---> |   SLAM    | ---> |  Mapping  |
   | (ViT‑DETR)  |      | (VIO/FG)  |      | (Semantic)|
   +-------------+      +-----------+      +-----------+
           |                   |                 |
           |                   |                 |
           v                   v                 v

   +-----------------------------------------------------------+
   |                    State Estimation                       |
   |   (Pose, Velocity, Covariance, Semantic World Model)      |
   +-----------------------------------------------------------+

           |
           v

   +----------------+      +-----------------------+
   |     MPC        | ---> | RL Steering Prior     |
   | (Trajectory    |      | (Gaussian PDF, PPO/TD3)|
   | Optimization)  |      +-----------------------+
   +----------------+                |
           |                         |
           v                         v

   +-----------------------------------------------------------+
   |                     Safety Supervisor                     |
   |   (Collision Avoidance, Emergency Braking, Fail‑Safe)     |
   +-----------------------------------------------------------+

           |
           v

   +---------------------------+
   |       UAV Actuators       |
   | (Motors, Control Surfaces)|
   +---------------------------+

🔍 Perception
DroNet (TensorRT FP16/INT8)
Depth Estimator
Semantic Segmentation
RViz visualization
Training + evaluation pipelines
Benchmarking + Jetson deployment tools


🧠 World Model
ViT encoder
Latent dynamics (GRU/Transformer)
Free‑space decoder
Risk decoder
Steering enhancer
TorchScript export pipeline


🗺 Mapping
Local occupancy grid
Global voxel + semantic map
🧭 Planning
Global planner (A* / D*)
Local MPC controller
Bayesian RL steering prior
🛡 Safety
Risk fusion
Safety modes
Rule engine
Emergency overrides

🎮 Control
MAVLink bridge
PX4 controller
Offboard mode manager
🧪 Simulation
AirSim scenario generator
PX4 SITL
Gazebo worlds

📦 Installation
bash
mkdir -p aurora_ws/src
cd aurora_ws/src
git clone https://github.com/em100/AURORA-ADAS.git
cd ..
colcon build --symlink-install
🎥 Demo Videos
(Add links when ready)

🧑‍💻 Maintainer
Emmanuel Musvaire  
AI/ML Engineer • Robotics Perception • Autonomous Systems

⭐ License

## ASCII Diagrams
All diagrams included in `/docs/diagrams/`.

## Installation
Clone the repo:git clone https://github.com/em100/emmusv.git

