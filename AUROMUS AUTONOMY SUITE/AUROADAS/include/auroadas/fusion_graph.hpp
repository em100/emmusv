#pragma once
#include <Eigen/Dense>
#include <vector>
#include <memory>
#include <rclcpp/rclcpp.hpp>

#include "auroadas/imu_preintegration.hpp"
#include "auroadas/gps_factor.hpp"
#include "auroadas/odometry_factor.hpp"
#include "auroadas/visual_factor.hpp"

namespace auroadas {

struct Pose {
    Eigen::Vector3d position;
    Eigen::Quaterniond orientation;
};

class FusionGraph {
public:
    FusionGraph(rclcpp::Logger logger);

    // Add factors
    void addImuMeasurement(const Eigen::Vector3d& accel,
                           const Eigen::Vector3d& gyro,
                           double dt);

    void addGpsMeasurement(double lat, double lon, double alt);

    void addOdometryMeasurement(const Eigen::Matrix4d& relative_pose);

    void addVisualMeasurement(const Eigen::Vector2d& uv,
                              const Eigen::Vector3d& landmark);

    // Run optimization (placeholder)
    Pose optimize();

private:
    rclcpp::Logger logger_;

    // Factors
    std::unique_ptr<ImuPreintegration> imu_;
    std::vector<GpsFactor> gps_factors_;
    std::vector<OdometryFactor> odom_factors_;
    std::vector<VisualFactor> visual_factors_;

    // Latest pose estimate
    Pose current_pose_;
};

} // namespace auroadas
