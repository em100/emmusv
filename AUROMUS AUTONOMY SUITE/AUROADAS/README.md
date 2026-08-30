# <p align="center">

# &#x20; <img src="https://img.shields.io/badge/AUROADAS-Autonomous%20Perception%20Stack-blue?style=for-the-badge">

# &#x20; <img src="https://img.shields.io/badge/ROS2-Humble-green?style=for-the-badge">

# &#x20; <img src="https://img.shields.io/badge/C++-17-red?style=for-the-badge">

# &#x20; <img src="https://img.shields.io/badge/SLAM-Factor%20Graph-yellow?style=for-the-badge">

# &#x20; <img src="https://img.shields.io/badge/ADAS-Ready-orange?style=for-the-badge">

# </p>

Branding banner (ASCII‑safe):
# 🚗 AUROADAS  
### *Real‑Time Multi‑Sensor Fusion & Perception for ADAS*


# 

# 

# AUROADAS‑Automotive

Real-Time Multi-Sensor Localization \& Perception System for ADAS Driving and Parking Features
C++17 • ROS2 • GTSAM • OpenCV • Automotive-Grade Architecture

# AUROADAS — Scalable Autonomy Stack (ADAS → ADS)

AUROADAS is a modular, multi‑sensor autonomy architecture designed to support both 
Advanced Driver Assistance Systems (ADAS, Levels 0–2) and Automated Driving Systems 
(ADS, Levels 3–5). It enhances driver assistance today while providing the perception, 
fusion, mapping, and planning foundation required for full autonomy.

---

## Features

### Perception
- Lane detection
- Object detection (vehicles, pedestrians)
- Drivable area segmentation
- Depth estimation
- Multi‑camera + LiDAR + radar integration

### Sensor Fusion
- Factor‑graph optimization (GTSAM‑style)
- Visual‑inertial odometry
- GPS drift correction
- LiDAR geometric constraints

### Mapping
- Real‑time local 3D maps
- Global HD maps
- Loop‑closure detection

### Planning
- Lane keeping (ADAS)
- Autonomous route planning (ADS)
- Collision risk estimation
- Safety overrides

### Control
- Smooth steering, throttle, brake commands
- Low‑pass filtering
- Full autonomous actuation in ADS mode

---

## Architecture Diagram
See `/docs/architecture/auroadas_architecture.png` for the full system diagram.

---

## ADAS → ADS Scalability
AUROADAS is designed to evolve:
- ADAS mode: human‑supervised assistance
- ADS mode: geofenced autonomy and full autonomous driving

---

## Getting Started
```bash
git clone https://github.com/em100/AUROADAS.git
cd AUROADAS
License
MIT License

Author
Emmanuel Musvaire  
Robotics Perception & Autonomous Systems Engineer


---

# **3.  Architecture Diagram




+---------------------------+
|       Sensors             |
|  Camera | LiDAR | Radar   |
|  IMU    | GPS             |
+---------------------------+
|
v
+---------------------------+
|   Perception Frontend     |
| NN Inference (lanes, objs)|
| Depth | Features | SemSeg |
+---------------------------+
|
v
+---------------------------+
|     Sensor Fusion         |
| Factor Graph | VIO | GPS  |
| LiDAR Geometry            |
+---------------------------+
|
v
+---------------------------+
|         Mapping           |
| Local 3D | Global HD Map  |
| Loop Closure              |
+---------------------------+
|
v
+---------------------------+
|         Planning          |
| ADAS: Lane Keeping        |
| ADS: Autonomous Routing   |
| Safety Overrides          |
+---------------------------+
|
v
+---------------------------+
|         Control           |
| Steering | Throttle | Brake|
| LPF | Autonomous Actuation |
+---------------------------+
|
v
+---------------------------+
|     Vehicle Interface     |
+---------------------------+























