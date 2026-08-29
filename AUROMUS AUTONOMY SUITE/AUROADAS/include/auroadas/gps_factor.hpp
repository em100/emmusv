#pragma once
#include <Eigen/Dense>
#include <rclcpp/rclcpp.hpp>
#include "auroadas/fusion_graph.hpp"

namespace auroadas {

class GpsFactor {
public:
    GpsFactor(rclcpp::Logger logger);

    void setMeasurement(double lat, double lon, double alt);

    Eigen::Vector3d error(const Pose& pose) const;

private:
    rclcpp::Logger logger_;

    double lat_ = 0.0;
    double lon_ = 0.0;
    double alt_ = 0.0;
};

} // namespace auroadas
