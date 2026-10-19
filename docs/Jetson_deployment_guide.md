\#⭐  Jetson Deployment Guide
#A clean, practical guide for Orin/Xavier/Nano.

\#Jetson Deployment Guide — AUROUAV

1. Flash Jetson
JetPack 5.x (Orin/Xavier)

JetPack 4.6 (Nano)

2. Install ROS2 Humble

sudo apt update
sudo apt install ros-humble-desktop

3. Install PX4 + MAVLink Tools

sudo apt install python3-pip
pip3 install mavsdk pymavlink

4. Install TensorRT + ONNX Runtime

sudo apt install python3-libnvinfer-dev onnxruntime



5. Clone AUROUAV
mkdir -p \~/auro\_ws/src
cd \~/auro\_ws/src
git clone https://github.com/em100/emmusv.git
cd ..
colcon build --symlink-install
6. Optimize Models
Convert DroNet → ONNX → TensorRT FP16/INT8

Convert ViT‑DETR → ONNX → TensorRT INT8

Export depth model → ONNX
7. Launch AUROUAV

ros2 launch auro\_uav auro\_uav.launch.py

