\# AUROADAS Performance



AUROADAS is designed for real‑time ADAS operation.



\---



\## Performance Targets



\- 30–60 Hz pipeline  

\- < 30 ms latency  

\- < 80% CPU/GPU utilization  

\- < 1% drift over long trajectories  



\---



\## Profiling Tools



\- `perf`  

\- `valgrind`  

\- ROS2 tracing (`ros2 trace`)  

\- RViz visualization  



\---



\## Bottlenecks



\- Visual frontend (feature extraction + tracking)  

\- IMU preintegration at high rates  

\- Factor graph optimization  

\- Mapping updates  



\---



\## Optimization Strategies



\- Zero‑copy message passing  

\- Preallocated buffers  

\- Efficient Eigen usage  

\- Sparse factor graph exploitation  

\- Reduced feature count under load  

\- Adaptive sensor fusion (drop low‑confidence sensors)  



\---



\## Real‑Time Guarantees



AUROADAS uses:

\- Fixed‑rate timers  

\- Bounded‑time fusion updates  

\- Priority scheduling for IMU + fusion  

\- Graceful degradation (IMU‑only fallback)  



