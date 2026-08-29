#include "auroadas/odometry_factor.hpp"
#include <rclcpp/rclcpp.hpp>

namespace auroadas {

OdometryFactor::OdometryFactor(rclcpp::Logger logger)
    : logger_(logger)
{
    RCLCPP_INFO(logger_, "OdometryFactor initialized");
}

void OdometryFactor::setRelativePose(const Eigen::Matrix4d& T) {
    relative_pose_ = T;
}

Eigen::VectorXd OdometryFactor::error(const Pose& from, const Pose& to) const {
    // Placeholder: compute pose error between nodes
    Eigen::Matrix4d T_from = Eigen::Matrix4d::Identity();
    T_from.block<3,1>(0,3) = from.position;
    T_from.block<3,3>(0,0) = from.orientation.toRotationMatrix();

    Eigen::Matrix4d T_to = Eigen::Matrix4d::Identity();
    T_to.block<3,1>(0,3) = to.position;
    T_to.block<3,3>(0,0) = to.orientation.toRotationMatrix();

    Eigen::Matrix4d T_err = (T_from.inverse() * T_to) - relative_pose_;

    Eigen::VectorXd err(6);
    err << T_err(0,3), T_err(1,3), T_err(2,3),
           0.0, 0.0, 0.0; // rotation error placeholder

    return err;
}

} // namespace auroadas
