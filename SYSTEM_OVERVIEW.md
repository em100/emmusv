📘 AURORA‑ADAS — System Overview
A Modular Autonomous Driving \& Navigation Stack for UAVs
Author: Emmanuel Musvaire  
Project: AURORA‑ADAS (Autonomous Drone Assistance System)  
Version: 2026

1. Introduction
AURORA‑ADAS is a fully modular, ROS2‑native autonomy stack designed for UAV navigation, perception, mapping, planning, and safety. It integrates:

GPU‑accelerated perception (DroNet, depth, semantics)

Predictive world‑modeling (ViT + latent dynamics)

Multi‑layer mapping (local + global)

Hierarchical planning (global + MPC local)

Safety supervision (risk fusion + rule engine)

PX4 offboard control (MAVLink bridge + controller)

Simulation‑driven development (AirSim + PX4 SITL)

The system is optimized for Jetson Orin / Xavier / Nano, and supports AirSim, Gazebo, and PX4 SITL.

1. High‑Level Architecture
2. Sensors → Perception → Estimation → World Model → Mapping → Planning → Safety → Control → PX4
Each subsystem is isolated, testable, and communicates via ROS2 topics.
3. Perception Subsystem
Responsibilities
Extract actionable signals from raw sensor data

Provide steering priors and collision probability

Produce depth maps and semantic masks

Feed latent embeddings to the world‑model

Components
DroNet (TensorRT FP16/INT8)

Depth Estimator (MiDaS / RAFT‑Stereo)

Semantic Segmentation (YOLO‑Seg / DeepLabv3)

TensorRT runtime

RViz visualization

Training + evaluation pipelines

Benchmarking + Jetson deployment tools

Outputs
/dronet/command → steering + collision

/depth/image → depth map

/semantic\_mask → segmentation

/camera/front/image\_raw → RGB

4. Estimation Subsystem
Responsibilities
Fuse IMU, VIO, SLAM into a stable state estimate

Provide pose for mapping, planning, and world‑model

Components
OpenVINS interface

IMU preintegration

EKF fusion

GTSAM SLAM backend

Loop closure detection

Outputs
/state/pose → fused pose

/vio/pose → VIO pose

/slam/pose → optimized SLAM pose

5. World‑Model Subsystem
Responsibilities
Predict future latent states

Estimate free‑space, risk, and enhanced steering

Provide predictive context for planning and safety

Components
ViT encoder

Latent dynamics (GRU / Transformer)

Free‑space decoder

Risk decoder

Steering enhancer

TorchScript export pipeline

Outputs
/world\_model/risk

/world\_model/steering

/world\_model/free\_space

6. Mapping Subsystem
Responsibilities
Build local occupancy grid

Build global voxel + semantic map

Provide spatial context for planning and safety

Components
Local Mapper (C++ + Python)

Global Mapper (C++ + Python)

Semantic fusion

Voxel map generation

Outputs
/local\_map

/global\_map

7. Planning Subsystem
Responsibilities
Compute global path

Generate local MPC trajectory

Integrate steering priors and risk signals

Components
Global Planner (A / D)\*\*

Local Planner (MPC)

Bayesian RL steering prior

Trajectory publisher

Outputs
/global\_path

/local\_trajectory

8. Safety Subsystem
Responsibilities
Fuse risk signals

Determine safety mode

Override control when necessary

Components
Risk fusion

Safety modes

Rule engine

Emergency handler

Outputs
/aurora/safety\_mode

/aurora/cmd\_vel (override)

9. Control Subsystem
Responsibilities
Convert planner commands into PX4 setpoints

Maintain offboard mode

Arm/disarm logic

Components
MAVLink bridge

PX4 controller

PX4 parameters

Outputs
/mavros/setpoint\_velocity/cmd\_vel\_unstamped

/mavros/set\_mode

/mavros/cmd/arming

10. Simulation Subsystem
Responsibilities
Provide realistic environments for training and testing

Generate DroNet datasets

Validate autonomy stack

Components
AirSim scenario generator

PX4 SITL

Gazebo worlds

Dataset generator

Scenario scripts (straight, slalom, collision)

11. End‑to‑End Data Flow

RGB → DroNet → Steering + Collision → Safety + MPC
RGB → Depth → Local Mapper → Planning
RGB → SemSeg → Global Mapper → Planning
RGB → ViT → Latent → Dynamics → Risk → Safety
IMU + VIO + SLAM → EKF → Pose → Mapping + Planning
Planning → Trajectory → PX4 Controller → MAVLink → PX4
12. Deployment Targets
Jetson Orin Nano

Jetson Xavier NX

Jetson Nano

PX4‑based UAVs

AirSim simulation

Gazebo + PX4 SITL

13. Design Principles
Modularity — each subsystem is isolated

Real‑time performance — TensorRT + MPC

Safety‑first — risk fusion + rule engine

Predictive autonomy — world‑model latent dynamics

Simulation‑driven development — AirSim + SITL

Jetson‑optimized — FP16/INT8 inference

14. Maintainer
Emmanuel Musvaire  
Independent AI/ML Engineer
Robotics Perception \& Autonomous Systems Specialist

