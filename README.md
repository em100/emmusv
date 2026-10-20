
<img width="4032" height="1070" alt="image" src="https://github.com/user-attachments/assets/fb079152-a529-4b3c-abf6-8bf39de170a7" />

<h1>System Architecture</h1>

<p>
AUROUAV is organized as a modular ROS 2 autonomy stack designed for
GNSS-denied navigation and autonomous aerial systems.
The architecture integrates perception, estimation, mapping,
planning, control, safety, and predictive world-model components
into a unified framework.
</p>

<ul>
<li>Perception Layer</li>
<li>Visual-Inertial Odometry (VIO)</li>
<li>SLAM and Localization</li>
<li>Semantic Mapping</li>
<li>Global Planning</li>
<li>Local Planning</li>
<li>Model Predictive Control</li>
<li>PX4 Flight Control Interface</li>
<li>Safety Monitoring</li>
<li>World Model Prediction</li>
<li>ROS 2 Jazzy Integration</li>
</ul>
<h1>AUROUAV Architecture Diagram</h1>
<img width="943" height="2268" alt="image" src="https://github.com/user-attachments/assets/876d5755-7121-40c6-b488-72dd3ea10bde" />

flowchart TD

    CAM[RGB Camera]
    IMU[IMU]

    CAM --> FT[Feature Tracking]
    FT --> VO[Visual Odometry]

    IMU --> IP[IMU Preintegration]

    VO --> EKF[Sensor Fusion]
    IP --> EKF

    EKF --> LC[Loop Closure]

    LC --> PG[Pose Graph Optimization]

    PG --> LOC[Localization]

    LOC --> MAP[Semantic Mapping]

    MAP --> GP[Global Planner]

    GP --> LP[Local Planner]

    LP --> MPC[Model Predictive Control]

    MPC --> PX4[PX4 Interface]

    MAP --> WM[World Model]

    WM --> RD[Risk Decoder]

    RD --> SAFE[Safety Supervisor]

    SAFE --> PX4



<h1>Core Capabilities</h1>

<ul>
<li>Visual-Inertial Odometry (VIO)</li>
<li>IMU Preintegration</li>
<li>EKF Sensor Fusion</li>
<li>Feature-Based SLAM</li>
<li>Loop Closure Detection</li>
<li>Pose Graph Optimization</li>
<li>Localization</li>
<li>Semantic Mapping</li>
<li>Occupancy Mapping</li>
<li>Point Cloud Mapping</li>
<li>Global Planning</li>
<li>Local Planning</li>
<li>Model Predictive Control (MPC)</li>
<li>PX4 Integration Framework</li>
<li>Safety Monitoring</li>
<li>Risk Fusion</li>
<li>Predictive World Models</li>
<li>ROS 2 Jazzy Integration</li>
</ul>
<h1>Repository Structure</h1>

<p>
AUROUAV is organized as a modular autonomy framework. Each subsystem is
implemented as an independent component to promote scalability,
maintainability, and deployment flexibility across simulation and
real-world platforms.
</p>

<pre>
AUROUAV/
│
├── control/
│   ├── px4_interface/
│   └── flight_control/
│
├── docs/
│
├── estimation/
│   ├── fusion_ekf/
│   ├── slam_backend_gtsam/
│   └── vio_frontend/
│
├── launch/
│
├── mapping/
│   ├── global_mapper/
│   └── local_mapper/
│
├── perception/
│   ├── dronet_perception/
│   ├── depth_estimator/
│   └── semantic_segmentation/
│
├── planning/
│   ├── global_planner/
│   └── local_planner/
│
├── ros2_ws/
│   └── src/
│
├── safety/
│   ├── rule_engine/
│   └── safety_monitor/
│
├── slam/
│   ├── feature_tracking/
│   ├── loop_closure/
│   ├── pose_graph/
│   └── localization/
│
├── vio/
│   ├── imu_preintegration/
│   ├── sensor_fusion/
│   └── visual_odometry/
│
└── world_model/
    ├── vit_encoder/
    ├── latent_dynamics/
    └── risk_decoder/
</pre>


<h1>Key Algorithms</h1>

<p>
AUROUAV integrates state-of-the-art algorithms for visual-inertial
navigation, graph-based SLAM, mapping, planning, control, safety,
and predictive world modeling.
</p>
<h1>Visual-Inertial Odometry</h1>

<ul>
<li>ORB Feature Extraction</li>
<li>Essential Matrix Estimation</li>
<li>Pose Recovery</li>
<li>IMU Preintegration</li>
<li>Visual-Inertial State Estimation</li>
</ul>
<h1>SLAM</h1>

<ul>
<li>Feature Tracking</li>
<li>Feature Matching</li>
<li>Loop Closure Detection</li>
<li>Pose Graph Optimization</li>
<li>Localization</li>
</ul>
<h1>Estimation</h1>

<ul>
<li>Extended Kalman Filter (EKF)</li>
<li>OpenVINS Integration</li>
<li>Sensor Fusion</li>
<li>State Propagation</li>
<li>Multi-Sensor Navigation</li>
</ul>
<h1>Mapping</h1>

<ul>
<li>Occupancy Grid Mapping</li>
<li>Point Cloud Mapping</li>
<li>Semantic Mapping</li>
<li>Environment Reconstruction</li>
<li>Traversability Analysis</li>
</ul>

<h1>Planning</h1>

<ul>
<li>A* Search</li>
<li>D* Search</li>
<li>Global Path Planning</li>
<li>Local Path Planning</li>
<li>Model Predictive Control (MPC)</li>
</ul>
<h1>Control</h1>

<ul>
<li>PX4 Interface</li>
<li>MAVLink Communication</li>
<li>Offboard Flight Control</li>
<li>Trajectory Tracking</li>
<li>Flight Command Execution</li>
</ul>


<h1>Safety</h1>

<ul>
<li>Risk Fusion</li>
<li>Rule-Based Safety Monitoring</li>
<li>Mission Health Assessment</li>
<li>Failure Detection</li>
<li>Emergency Response Handling</li>
</ul>

<h1>World Models</h1>

<ul>
<li>Vision Transformer Encoders</li>
<li>Latent Dynamic Models</li>
<li>Risk Decoding</li>
<li>Predictive World Modeling</li>
<li>Free-Space Prediction</li>
</ul>

<h1>ROS 2 Packages</h1>

<p>
AUROUAV is implemented as a modular ROS 2 Jazzy autonomy stack.
Each package encapsulates a specific subsystem and communicates
through ROS 2 topics, services, and actions.
</p>

<h1>ROS 2 Packages</h1>

<ul>
<li><strong>auro_uav_perception</strong> - Perception and scene understanding</li>

<li><strong>auro_uav_slam</strong> - VIO, SLAM, localization, and pose estimation</li>

<li><strong>auro_uav_mapping</strong> - Occupancy, point-cloud, and semantic mapping</li>

<li><strong>auro_uav_planning</strong> - Global planning, local planning, and MPC</li>

<li><strong>auro_uav_control</strong> - PX4 interface, MAVLink bridge, and flight control</li>

<li><strong>auro_uav_safety</strong> - Risk fusion, safety supervision, and emergency handling</li>

<li><strong>auro_uav_world_model</strong> - Predictive world models and latent dynamics</li>

<li><strong>auro_uav_msgs</strong> - Custom ROS 2 messages and interfaces</li>

<li><strong>auro_uav_bringup</strong> - System launch and orchestration</li>
</ul>

<h2>Representative Robotics Implementations</h2>

<p>
The files below demonstrate practical implementations of
Visual-Inertial Odometry (VIO), feature-based SLAM,
loop closure detection, pose graph optimization,
and localization for autonomous navigation systems.
</p>

<h1>Source Code References</h1>

<p>
The following implementations represent the core Visual-Inertial
Odometry (VIO) and SLAM algorithms developed for AUROUAV.
These modules provide examples of feature extraction, visual odometry,
IMU processing, localization, loop closure detection, and graph-based
state estimation.
</p>
<h2>Visual-Inertial Odometry (VIO)</h2>

<ul>

<li>
Visual Odometry Implementation
<br>
<a href="https://github.com/em100/emmusv/blob/main/vio/visual_odometry/visual_odometry.cpp">
visual_odometry.cpp
</a>
</li>

<li>
Visual Odometry Header
<br>
<a href="https://github.com/em100/emmusv/blob/main/vio/visual_odometry/visual_odometry.hpp">
visual_odometry.hpp
</a>
</li>

<li>
IMU Preintegration Implementation
<br>
<a href="https://github.com/em100/emmusv/blob/main/vio/imu_preintegration/imu_preintegration.cpp">
imu_preintegration.cpp
</a>
</li>

<li>
IMU Preintegration Header
<br>
<a href="https://github.com/em100/emmusv/blob/main/vio/imu_preintegration/imu_preintegration.hpp">
imu_preintegration.hpp
</a>
</li>

</ul>

<h2>SLAM</h2>

<ul>

<li>
Feature Tracking
<br>
<a href="https://github.com/em100/emmusv/blob/main/slam/feature_tracking/feature_tracker.cpp">
feature_tracker.cpp
</a>
</li>

<li>
Loop Closure Detection
<br>
<a href="https://github.com/em100/emmusv/blob/main/slam/loop_closure/loop_closure.cpp">
loop_closure.cpp
</a>
</li>

<li>
Pose Graph Optimization
<br>
<a href="https://github.com/em100/emmusv/blob/main/slam/pose_graph/pose_graph.cpp">
pose_graph.cpp
</a>
</li>

<li>
Localization
<br>
<a href="https://github.com/em100/emmusv/blob/main/slam/localization/localization.cpp">
localization.cpp
</a>
</li>

</ul>


<h1>Build</h1>

<p>
The AUROUAV autonomy stack is designed for Ubuntu Linux and ROS 2 Jazzy.
The following dependencies are required to build the core robotics,
computer vision, mapping, planning, and autonomy modules.
</p>

<h1>Dependencies</h1>

<p>
Install the required development tools, libraries, and computer vision
frameworks before building AUROUAV.
</p>

<pre>
sudo apt update

sudo apt install \
build-essential \
cmake \
git \
libopencv-dev \
libeigen3-dev
</pre>

<h1>ROS 2 Jazzy</h1>

<p>
Source the ROS 2 Jazzy environment before building any ROS 2 packages.
</p>

<pre>
source /opt/ros/jazzy/setup.bash
</pre>

<h1>Build ROS 2 Workspace</h1>

<p>
Compile all AUROUAV ROS 2 packages using the Colcon build system.
</p>

<pre>
cd ros2_ws

colcon build --symlink-install
</pre>

<h1>Source Workspace</h1>

<p>
Load the compiled ROS 2 packages into the current shell environment.
</p>

<pre>
source install/setup.bash
</pre>

<h1>Launch AUROUAV</h1>

<p>
Launch the complete autonomy stack including perception,
SLAM, mapping, planning, control, safety, and world models.
</p>

<pre>
ros2 launch auro_uav_bringup auro_uav.launch.py
</pre>

<h1>Launch SLAM Subsystem</h1>

<p>
Launch the complete SLAM pipeline including feature tracking,
visual odometry, loop closure, pose graph optimization,
and localization.
</p>

<pre>
ros2 launch auro_uav_slam slam.launch.py
</pre>



<h1>Launch World Model</h1>

<p>
Launch the predictive world model components including
ViT encoding, latent dynamics, risk estimation, and
free-space prediction.
</p>

<pre>
ros2 launch auro_uav_world_model world_model.launch.py
</pre>


<h1>Technologies</h1>

<ul>
<li>ROS 2 Jazzy</li>
<li>C++17</li>
<li>OpenCV</li>
<li>Eigen</li>
<li>GTSAM</li>
<li>OpenVINS</li>
<li>PX4</li>
<li>MAVLink</li>
<li>Model Predictive Control</li>
<li>Semantic Mapping</li>
</ul>

<h1>Author</h1>

<p>
<strong>Emmanuel Musvaire</strong>
</p>

<ul>
<li>Independent AI/ML Engineer</li>
<li>Robotics Perception Specialist</li>
<li>Autonomous Systems Researcher</li>
</ul>

<p>
GitHub:
<a href="https://github.com/em100/emmusv.git">https://github.com/em100/emmusv.git/</a>
</p>
<p>
MY GitHub Website:
<a href=" https://em100.github.io/emmusv">https://em100.github.io/emmusv</a>
</p>
<p>
Portfolio:
<a href="https://sites.google.com/musvtech.org/musvtech-org">
https://sites.google.com/musvtech.org/musvtech-org
</a>
</p>

<p>
Research Focus: Human-Centered AI, Visual-Inertial Navigation,
SLAM, Autonomous UAV Systems, Robotics Perception, Semantic Mapping,
and Predictive World Models.
</p>

<h1>Research Areas</h1>

<ul>
<li>Robotics Perception and Scene Understanding</li>
<li>Visual-Inertial Navigation Systems (VINS)</li>
<li>Graph-Based SLAM and Pose Graph Optimization</li>
<li>Semantic Mapping and World Modeling</li>
<li>GNSS-Denied Navigation</li>
<li>Autonomous UAV Systems</li>
<li>Multi-Sensor Fusion</li>
<li>Model Predictive Control (MPC)</li>
<li>Human-Centered AI</li>
<li>Reinforcement Learning for Autonomous Decision Making</li>
</ul>






