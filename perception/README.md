**AURORA‑ADAS Perception Module**

DroNet • Depth • Semantic Segmentation • TensorRT • World‑Model Inputs

The Perception subsystem of AURORA‑ADAS converts raw sensor data (RGB, depth, semantic masks) into actionable signals for downstream modules:



Steering priors for Local Planner (MPC)



Collision probability for Safety Supervisor



Dense geometry for Local Mapper



Semantic classes for Global Mapper



Latent embeddings for the World Model



This folder contains all perception‑related models, nodes, training pipelines, and deployment tools.



🏗 Directory Structure



perception/

├── dronet\_perception/

│   ├── CMakeLists.txt

│   ├── package.xml

│   ├── msg/DronetCommand.msg

│   ├── include/

│   │   ├── inference\_engine.hpp

│   │   └── dronet\_node.hpp

│   ├── src/

│   │   ├── dronet\_node.cpp

│   │   └── inference\_engine.cpp

│   ├── models/

│   │   ├── dronet.onnx

│   │   ├── dronet\_fp16.engine

│   │   └── dronet\_int8.engine

│   ├── tensorrt/

│   │   ├── build\_engine.py

│   │   ├── calibrator.py

│   │   └── benchmark\_tensorrt.py

│   └── training/

│       ├── airsim\_dataset\_generator.py

│       ├── dataset\_builder.py

│       ├── train\_dronet.py

│       ├── eval\_dronet.py

│       ├── build\_calibration\_dataset.py

│       └── config\_dronet.yaml

│

├── depth\_estimator/

│   ├── include/

│   └── src/

│

└── semantic\_segmentation/

&#x20;   ├── include/

&#x20;   └── src/





🚀 DroNet: Steering + Collision Probability

DroNet is a lightweight CNN that predicts:



steering ∈ \[-1, 1]



collision probability ∈ \[0, 1]



It runs in real‑time on Jetson using TensorRT.



Runtime Topics



| Topic | Type | Description |

| --- | --- | --- |

| ``/dronet/command`` | ``DronetCommand`` | Steering + collision probability |

| ``/camera/front/image\_raw`` | ``sensor\_msgs/Image`` | Input RGB |



⚙️ DroNet Models



| File | Precision | Purpose |

| --- | --- | --- |

| ``dronet.onnx`` | FP32 | Portable ONNX model exported from PyTorch |

| ``dronet\_fp16.engine`` | FP16 | Optimized TensorRT engine (default) |

| ``dronet\_int8.engine`` | INT8 | Ultra‑fast quantized engine |



These are generated using:



train\_dronet.py → produces dronet.onnx



build\_engine.py → produces FP16 / INT8 engines



calibrator.py → builds INT8 calibration cache





































