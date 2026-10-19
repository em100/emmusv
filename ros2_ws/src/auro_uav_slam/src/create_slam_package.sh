#!/usr/bin/env bash

set -e

PKG=~/AUROUAV_outer/AUROUAV/ros2_ws/src/auro_uav_slam

mkdir -p $PKG/src
mkdir -p $PKG/include/auro_uav_slam
mkdir -p $PKG/launch
mkdir -p $PKG/config

NODES=(
feature_tracker
visual_odometry
loop_closure
pose_graph
localization
)

for NODE in "${NODES[@]}"
do

cat > "$PKG/src/${NODE}.cpp" << EOF
#include <rclcpp/rclcpp.hpp>

class ${NODE^}Node : public rclcpp::Node
{
public:
    ${NODE^}Node()
    : Node("${NODE}")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "${NODE} node started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<${NODE^}Node>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
EOF

done

echo "SLAM source files generated successfully."