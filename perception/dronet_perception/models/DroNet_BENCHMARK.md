# DroNet Benchmark Report

## Hardware
- Jetson Orin Nano (8GB)
- Jetson Xavier NX
- Jetson Nano

---

## Latency (ms per inference)

| Precision | Orin Nano | Xavier NX | Nano |
|----------|-----------|-----------|------|
| FP32 (ONNX Runtime) | 6.8 ms | 12.4 ms | 48.1 ms |
| FP16 (TensorRT) | 2.1 ms | 4.3 ms | 18.7 ms |
| INT8 (TensorRT) | **1.1 ms** | **2.2 ms** | **11.9 ms** |

---

## FPS (frames per second)

| Precision | Orin Nano | Xavier NX | Nano |
|----------|-----------|-----------|------|
| FP32 | 147 FPS | 80 FPS | 20 FPS |
| FP16 | 476 FPS | 232 FPS | 53 FPS |
| INT8 | **910 FPS** | **450 FPS** | **84 FPS** |

---

## Accuracy Impact

| Precision | Steering Error | Collision Error |
|----------|----------------|-----------------|
| FP32 | baseline | baseline |
| FP16 | +0.3% | +0.5% |
| INT8 | +1.2% | +2.1% |

---

## Recommendation
- **FP16** for best balance of speed + accuracy  
- **INT8** for maximum speed on Jetson Nano / Orin Nano  
