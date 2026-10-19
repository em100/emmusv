#Jetson Deployment Installer (setup.sh)

#!/bin/bash

echo "=== AUROUAV Jetson Setup ==="

sudo apt update && sudo apt upgrade -y

echo "[1] Installing ROS2 Humble..."
sudo apt install -y ros-humble-desktop ros-humble-perception ros-humble-cv-bridge

echo "[2] Installing PX4 dependencies..."
sudo apt install -y python3-pip python3-empy python3-toml
pip3 install mavsdk

echo "[3] Installing TensorRT + ONNX Runtime..."
sudo apt install -y python3-libnvinfer-dev onnxruntime

echo "[4] Building AUROUAV workspace..."
mkdir -p ~/auro_ws/src
cd ~/auro_ws/src
git clone https://github.com/em100/emmusv.git
cd ..
colcon build --symlink-install

echo "=== AUROUAV Setup Complete ==="
