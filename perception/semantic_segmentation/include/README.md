###perception/README.md

# AUROUAV Perception Module

This package provides GPU‑accelerated perception for AUROUAV, including:

- DroNet (steering + collision)
- Depth estimation (ONNX/TensorRT)
- Semantic segmentation
- ViT‑DETR object detection

### Nodes
- dronet_node
- depth_node
- semseg_node
- vit_detr_node

### Outputs
- /auro_uav/steering
- /auro_uav/collision_prob
- /auro_uav/depth_map
- /auro_uav/semantics
- /auro_uav/detections

### Deployment
Optimized for Jetson Orin/Xavier/Nano using TensorRT FP16/INT8.
