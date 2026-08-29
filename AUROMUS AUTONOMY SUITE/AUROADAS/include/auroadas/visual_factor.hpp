#pragma once
#include <Eigen/Dense>
#include <rclcpp/rclcpp.hpp>
#include "auroadas/fusion_graph.hpp"

namespace auroadas {

class VisualFactor {
public:
    VisualFactor(rclcpp::Logger logger);

    void setObservation(const Eigen::Vector2d& uv);

    Eigen::Vector2d error(const Pose& pose,
                          const Eigen::Vector3d& landmark) const;

private:
    rclcpp::Logger logger_;
    Eigen::Vector2d uv_{0.0, 0.0};
};

} // namespace auroadas
