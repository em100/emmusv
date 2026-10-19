#!/usr/bin/env bash

PKG=~/AUROUAV_outer/AUROUAV/ros2_ws/src/auro_uav_slam

declare -A MAP

MAP["feature_tracker"]="FeatureTrackerNode"
MAP["visual_odometry"]="VisualOdometryNode"
MAP["loop_closure"]="LoopClosureNode"
MAP["pose_graph"]="PoseGraphNode"
MAP["localization"]="LocalizationNode"

for NODE in "${!MAP[@]}"
do

CLASS=${MAP[$NODE]}

cat > "$PKG/src/$NODE.cpp" << EOF
#include <rclcpp/rclcpp.hpp>

class $CLASS : public rclcpp::Node
{
public:

    $CLASS()
    : Node("$NODE")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "$NODE node started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<$CLASS>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
EOF

done

echo "AUROUAV SLAM nodes generated."
