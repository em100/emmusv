\# AUROADAS Testing \& Validation



AUROADAS is validated using simulation, bag playback, and on‑road testing.



\---



\## Simulation Testing



\### CARLA



1\. Launch CARLA:

./CarlaUE4.sh -quality-level=Epic





2\. Use ROS2 bridge to publish:

\- Camera images  

\- IMU  

\- GPS  

\- Odometry  

\- LiDAR  



3\. Map topics to AUROADAS:



/carla/.../camera → /camera/front/image\_raw

/carla/.../imu → /imu/data

/carla/.../gnss → /gps/fix

/carla/.../odometry → /vehicle/odometry

/carla/.../lidar → /lidar/points





4\. Launch AUROADAS:

ros2 launch auroadas system.launch.py





\---



\### LGSVL / SVL



\- Configure ego vehicle with ROS2 bridge  

\- Same topic mapping as CARLA  

\- Test ADAS scenarios (lane keeping, parking, obstacle avoidance)



\---



\## Bag Playback



Record:

ros2 bag record /camera/front/image\_raw /imu/data /gps/fix /vehicle/odometry





Replay:

ros2 bag play <bag>





\---



\## On‑Road Testing



Evaluate:

\- Drift  

\- Loop closure accuracy  

\- Obstacle detection  

\- Tracking stability  

\- Confidence score  



\---



\## Metrics



\- Drift < 1%  

\- Loop closure correction < 0.3 m  

\- Latency < 30 ms  

\- Obstacle detection accuracy > 90%  



