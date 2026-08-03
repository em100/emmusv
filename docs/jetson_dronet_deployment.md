# DroNet Deployment on NVIDIA Jetson

## 1. Install JetPack
JetPack 5.x recommended.

Includes:
- CUDA
- cuDNN
- TensorRT
- OpenCV

---

## 2. Copy DroNet Models
Place the following in:

- `dronet_fp16.engine`
- `dronet_int8.engine`
- `dronet.onnx`

---

## 3. Run DroNet Node

```bash
ros2 launch dronet_perception dronet.launch.py
