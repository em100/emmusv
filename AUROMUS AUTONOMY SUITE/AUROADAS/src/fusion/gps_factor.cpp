#include "auroadas/gps_factor.hpp"
#include <rclcpp/rclcpp.hpp>

namespace auroadas {

GpsFactor::GpsFactor(rclcpp::Logger logger)
    : logger_(logger)
{
    RCLCPP_INFO(logger_, "GpsFactor initialized");
}

void GpsFactor::setMeasurement(double lat, double lon, double alt) {
    lat_ = lat;
    lon_ = lon;
    alt_ = alt;
}

Eigen::Vector3d GpsFactor::error(const Pose& pose) const {
    // Placeholder: convert GPS to ENU or map frame
    Eigen::Vector3d gps_pos(lat_, lon_, alt_);
    return pose.position - gps_pos;
}

} // namespace auroadas
