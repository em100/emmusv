# DroNet Model Card

## Model Summary
DroNet is a lightweight convolutional neural network designed for real‑time UAV navigation.  
It predicts:

- **Steering angle** ∈ [-1, 1]  
- **Collision probability** ∈ [0, 1]

The model is optimized using TensorRT for deployment on NVIDIA Jetson platforms.

---

## Intended Use
DroNet is used inside **AURORA‑ADAS** for:

- Reactive obstacle avoidance  
- Steering priors for MPC  
- Safety monitoring (collision probability)

---

## Training Data
DroNet was trained on:

- AirSim simulated drone flights  
- Random exploration trajectories  
- Human‑demonstrated trajectories  
- Collision events (binary labels)

Dataset size: **~200k images**

---

## Model Architecture
- Input: 200×200 RGB  
- Backbone: ResNet‑8 style CNN  
- Output: 2‑dimensional vector  
  - steering  
  - collision probability  

---

## Exported Artifacts
| File | Format | Precision | Purpose |
|------|--------|-----------|---------|
| `dronet.onnx` | ONNX | FP32 | Portable model |
| `dronet_fp16.engine` | TensorRT | FP16 | Default runtime engine |
| `dronet_int8.engine` | TensorRT | INT8 | Ultra‑fast runtime engine |

---

## Performance
- Jetson Orin Nano: **~450 FPS (INT8)**  
- Jetson Xavier NX: **~220 FPS (FP16)**  
- Jetson Nano: **~45 FPS (INT8)**  

---

## Ethical Considerations
DroNet should not be used for:

- Human detection  
- Surveillance  
- Weaponized drones  

It is strictly for **safe autonomous navigation**.

---

## Maintainer
**Emmanuel Musvaire**  
AURORA‑ADAS Project  
