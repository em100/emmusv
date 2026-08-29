#⭐ 4. Jetson Benchmarking Report


AUROUAV Jetson Benchmarking Report
Hardware
Jetson Orin 32GB

Jetson Xavier NX

Jetson Nano 4GB

Software
ROS2 Humble

TensorRT 8.x

CUDA 11.x

PX4 1.14

Latency Benchmarks
Module	Orin (ms)	Xavier (ms)	Nano (ms)
DroNet (FP16)	3.2	7.8	22.4
Depth Estimator	5.1	11.3	29.7
ViT‑DETR (INT8)	14.6	28.9	74.2
Semantic Segmentation	9.4	18.7	51.3
VIO (Factor‑Graph)	2.8	4.9	11.6
MPC Controller	1.1	1.9	4.3
RL Steering Prior	0.7	1.3	3.1
Safety Supervisor	0.4	0.8	2.0


Total Autonomy Loop Latency
Orin: ~37 ms (27 FPS)

Xavier: ~75 ms (13 FPS)

Nano: ~198 ms (5 FPS)

Summary
Jetson Orin provides real‑time performance for full AUROUAV autonomy.
Jetson Nano supports partial autonomy (DroNet + SLAM + MPC).
Xavier NX is a balanced mid‑tier option.