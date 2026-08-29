### 4.5 DroNet Ablation Study

To understand the contribution of each design choice in DroNet, we conducted an ablation study on the AirSim dataset.

#### 4.5.1 Backbone Depth

We compared shallow and deeper variants of the convolutional backbone:

- **DroNet‑S (shallow)**: 2 conv blocks  
- **DroNet‑B (baseline)**: 3 conv blocks  
- **DroNet‑D (deep)**: 5 conv blocks  

Results showed that DroNet‑B provided the best trade‑off between accuracy and latency, with DroNet‑D offering marginal gains at significantly higher computational cost.

#### 4.5.2 Collision Head vs. Steering‑Only

We evaluated a steering‑only model against the dual‑head DroNet:

- **Steering‑only**: single regression head  
- **DroNet dual‑head**: steering + collision probability  

The dual‑head architecture improved safety performance by providing an explicit collision probability signal, which the safety subsystem could use independently of the steering output.

#### 4.5.3 Quantization (FP32 vs FP16 vs INT8)

We compared FP32, FP16, and INT8 deployments:

- FP16 preserved almost all accuracy while significantly reducing latency.  
- INT8 introduced a small accuracy drop but enabled ultra‑low‑latency inference on Jetson devices.

Overall, the ablation study supports the chosen baseline: a compact backbone, dual‑head architecture, and FP16/INT8 deployment for embedded platforms.
