# AURORA‑ADAS System Architecture

## 1. Overview

AURORA‑ADAS is a modular autonomy stack for UAVs, designed around ROS2, PX4, and GPU‑accelerated perception. The system is decomposed into:

- Perception
- World Model
- Mapping
- Planning
- Safety
- Control (PX4 + MAVLink)
- Simulation (AirSim, Gazebo)

Each subsystem communicates via ROS2 topics, services, and parameters.

---

## 2. High‑Level Data Flow

1. Sensors (RGB, IMU, depth, semantics) → Perception
2. Perception → Steering, collision, depth, semantic masks
3. Perception + Estimation → World Model latent state
4. World Model + Mapping → Free‑space, risk, global context
5. Planning → Trajectories (global + local)
6. Safety → Mode selection, overrides
7. Control → PX4 setpoints, MAVLink commands

---

## 3. Subsystems

### 3.1 Perception

- DroNet (steering + collision)
- Depth estimator
- Semantic segmentation
- TensorRT engines
- RViz visualization

### 3.2 Estimation

- VIO frontend (OpenVINS)
- IMU preintegration
- EKF fusion
- SLAM backend (GTSAM)

### 3.3 Mapping

- Local occupancy grid
- Global voxel + semantic map

### 3.4 World Model

- ViT encoder
- Latent dynamics (GRU/Transformer)
- Free‑space, risk, steering predictors

### 3.5 Planning

- Global planner (A*/D*)
- Local MPC controller
- Bayesian RL prior integration

### 3.6 Safety

- Risk fusion
- Safety modes
- Rule engine
- Overrides to PX4

### 3.7 Control

- MAVLink bridge
- PX4 controller
- PX4 parameters

---

## 4. Simulation Integration

- AirSim for dataset generation and scenario testing
- Gazebo + PX4 SITL for physics‑based validation

---

## 5. Deployment Targets

- Jetson Orin / Xavier / Nano
- PX4‑based UAVs
- ROS2 (Foxy/Humble)

---

## 6. Design Principles

- Modular
- Real‑time capable
- Safety‑aware
- Simulation‑driven development
