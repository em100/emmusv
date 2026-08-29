

\---



\# 📐 \*\*`docs/math.md`\*\*



```markdown

\# AUROADAS Mathematical Foundations



AUROADAS relies on classical robotics, SLAM, and VIO mathematics. This document summarizes the core equations.



\---



\## IMU Preintegration



State:

\- Position: p  

\- Velocity: v  

\- Orientation: q  

\- Biases: b\_a, b\_g  



Preintegration accumulates IMU measurements between frames:



Δp = v \* dt + 0.5 \* R(q) \* (a - b\_a) \* dt²

Δv = R(q) \* (a - b\_a) \* dt

Δq = q ⊗ Exp((ω - b\_g) \* dt)





Where:

\- `Exp()` is the SO(3) exponential map  

\- `R(q)` is rotation matrix from quaternion  



\---



\## Factor Graph



Variables:

\- Pose\_i = {p\_i, q\_i}

\- Velocity\_i

\- Biases\_i



Factors:

\- \*\*IMU factor\*\*: links consecutive states  

\- \*\*GPS factor\*\*: absolute position constraint  

\- \*\*Odometry factor\*\*: relative pose constraint  

\- \*\*Visual factor\*\*: reprojection error  



Optimization:





Where:

\- `Exp()` is the SO(3) exponential map  

\- `R(q)` is rotation matrix from quaternion  



\---



\## Factor Graph



Variables:

\- Pose\_i = {p\_i, q\_i}

\- Velocity\_i

\- Biases\_i



Factors:

\- \*\*IMU factor\*\*: links consecutive states  

\- \*\*GPS factor\*\*: absolute position constraint  

\- \*\*Odometry factor\*\*: relative pose constraint  

\- \*\*Visual factor\*\*: reprojection error  



Optimization:



argmin\_x Σ ||f\_i(x)||²





Using Levenberg‑Marquardt.



\---



\## Visual Reprojection



Landmark L in world → camera frame:



P\_c = R(q)^T (L - p)

u = fx \* (P\_c.x / P\_c.z) + cx

v = fy \* (P\_c.y / P\_c.z) + cy





Error:

e = \[u, v] - measurement





\---



\## Mapping



Local map:

\- Point cloud or voxel grid  

\- Updated using pose graph corrections  



Pose graph:

\- Nodes: poses  

\- Edges: constraints (odom, loop closure)  



Loop closure detection:

\- Euclidean distance threshold  





































































