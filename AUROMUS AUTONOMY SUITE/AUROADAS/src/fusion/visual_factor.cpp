#include "auroadas/visual_factor.hpp"
#include <rclcpp/rclcpp.hpp>

namespace auroadas {

VisualFactor::VisualFactor(rclcpp::Logger logger)
    : logger_(logger)
{
    RCLCPP_INFO(logger_, "VisualFactor initialized");
}

void VisualFactor::setObservation(const Eigen::Vector2d& uv) {
    uv_ = uv;
}

Eigen::Vector2d VisualFactor::error(const Pose& pose,
                                    const Eigen::Vector3d& landmark) const
{
    // Placeholder pinhole projection
    Eigen::Vector3d Pc = pose.orientation.inverse() * (landmark - pose.position);

    if (Pc.z() <= 0.0) {
        return Eigen::Vector2d(0, 0);
    }

    Eigen::Vector2d proj(Pc.x() / Pc.z(), Pc.y() / Pc.z());
    return proj - uv_;
}

} // namespace auroadas
