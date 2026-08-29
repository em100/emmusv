#pragma once
#include <Eigen/Dense>
#include <rclcpp/rclcpp.hpp>
#include "auroadas/fusion_graph.hpp"

namespace auroadas {

struct PoseGraphEdge;

class OdometryFactor {
public:
    OdometryFactor(rclcpp::Logger logger);

    void setRelativePose(const Eigen::Matrix4d& T);

    Eigen::VectorXd error(const Pose& from, const Pose& to) const;

private:
    rclcpp::Logger logger_;
    Eigen::Matrix4d relative_pose_ = Eigen::Matrix4d::Identity();
};

} // namespace auroadas
