🌌 AURORA‑ADAS
Autonomous Drone Assistance System
Robotics • Perception • World‑Modeling • Planning • Safety • PX4



🚀 Overview
AURORA‑ADAS is a modular autonomy stack for UAVs, integrating:

GPU‑accelerated perception (DroNet, depth, semantics)

Predictive world‑modeling (ViT + latent dynamics)

Multi‑layer mapping (local + global)

Hierarchical planning (A\* + MPC)

Safety supervision (risk fusion + rule engine)

PX4 offboard control (MAVLink bridge + controller)

Simulation‑driven development (AirSim + PX4 SITL)

Designed for Jetson Orin / Xavier / Nano and PX4‑based UAVs.





🧩 System Architecture

Sensors → Perception → Estimation → World Model → Mapping → Planning → Safety → Control → PX4
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
Global planner (A\* / D\*)

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
mkdir -p aurora\_ws/src
cd aurora\_ws/src
git clone https://github.com/em100/AURORA-ADAS.git
cd ..
colcon build --symlink-install
🎥 Demo Videos
(Add links when ready)



🧑‍💻 Maintainer
Emmanuel Musvaire  
AI/ML Engineer • Robotics Perception • Autonomous Systems



⭐ License
MIT License





