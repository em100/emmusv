============================================================
                    AUROUAV API Reference
============================================================

PERCEPTION API
--------------
Topic: /auro_uav/steering
Type: std_msgs/Float32
Description: DroNet steering angle output.

Topic: /auro_uav/collision_prob
Type: std_msgs/Float32
Description: DroNet collision probability.

Topic: /auro_uav/depth_map
Type: sensor_msgs/Image (32FC1)
Description: Depth estimator output.

Topic: /auro_uav/semantics
Type: sensor_msgs/Image
Description: Semantic segmentation mask.

Topic: /auro_uav/detections
Type: vision_msgs/Detection2DArray
Description: ViT‑DETR object detections.


SLAM API
--------
Topic: /auro_uav/pose
Type: geometry_msgs/PoseStamped

Topic: /auro_uav/velocity
Type: geometry_msgs/TwistStamped

Topic: /auro_uav/covariance
Type: std_msgs/Float32MultiArray


MAPPING API
-----------
Topic: /auro_uav/local_map
Type: nav_msgs/OccupancyGrid

Topic: /auro_uav/global_map
Type: auro_uav_msgs/VoxelMap

Topic: /auro_uav/semantic_map
Type: auro_uav_msgs/SemanticVoxelMap


PLANNING + CONTROL API
----------------------
Topic: /auro_uav/mpc_cmd
Type: auro_uav_msgs/ControlCmd

Topic: /auro_uav/rl_prior
Type: std_msgs/Float32MultiArray (Gaussian μ, σ)

Topic: /mavros/setpoint_raw/local
Type: mavros_msgs/PositionTarget


SAFETY API
----------
Topic: /auro_uav/risk
Type: std_msgs/Float32

Topic: /auro_uav/safety_mode
Type: std_msgs/String

Topic: /auro_uav/emergency_stop
Type: std_msgs/Bool
