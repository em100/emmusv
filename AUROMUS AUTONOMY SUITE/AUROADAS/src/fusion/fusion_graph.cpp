#include "auroadas/fusion_graph.hpp"

namespace auroadas {

FusionGraph::FusionGraph(rclcpp::Logger logger)
    : logger_(logger)
{
    imu_ = std::make_unique<ImuPreintegration>(logger_);

    current_pose_.position = Eigen::Vector3d::Zero();
    current_pose_.orientation = Eigen::Quaterniond::Identity();

    RCLCPP_INFO(logger_, "FusionGraph initialized");
}

// -------------------------------------------------------------
// IMU Integration
// -------------------------------------------------------------
void FusionGraph::addImuMeasurement(const Eigen::Vector3d& accel,
                                    const Eigen::Vector3d& gyro,
                                    double dt)
{
    imu_->integrate(accel, gyro, dt);
}

// -------------------------------------------------------------
// GPS Factor
// -------------------------------------------------------------
void FusionGraph::addGpsMeasurement(double lat, double lon, double alt)
{
    GpsFactor factor(logger_);
    factor.setMeasurement(lat, lon, alt);
    gps_factors_.push_back(factor);
}

// -------------------------------------------------------------
// Odometry Factor
// -------------------------------------------------------------
void FusionGraph::addOdometryMeasurement(const Eigen::Matrix4d& relative_pose)
{
    OdometryFactor factor(logger_);
    factor.setRelativePose(relative_pose);
    odom_factors_.push_back(factor);
}

// -------------------------------------------------------------
// Visual Factor
// -------------------------------------------------------------
void FusionGraph::addVisualMeasurement(const Eigen::Vector2d& uv,
                                       const Eigen::Vector3d& landmark)
{
    VisualFactor factor(logger_);
    factor.setObservation(uv);
    visual_factors_.push_back(factor);
}

// -------------------------------------------------------------
// Optimization (placeholder)
// -------------------------------------------------------------
Pose FusionGraph::optimize()
{
    // 1. Apply IMU preintegration deltas
    current_pose_.position += imu_->deltaP();
    current_pose_.orientation = imu_->deltaQ() * current_pose_.orientation;

    // 2. Apply GPS corrections (very simplified)
    for (const auto& gps : gps_factors_) {
        Eigen::Vector3d err = gps.error(current_pose_);
        current_pose_.position -= 0.1 * err;  // small correction
    }

    // 3. Apply odometry constraints (simplified)
    for (const auto& odom : odom_factors_) {
        Eigen::VectorXd err = odom.error(current_pose_, current_pose_);
        current_pose_.position -= 0.05 * err.head<3>();
    }

    // 4. Apply visual reprojection corrections (simplified)
    for (const auto& vis : visual_factors_) {
        Eigen::Vector3d dummy_landmark(1.0, 1.0, 5.0);
        Eigen::Vector2d err = vis.error(current_pose_, dummy_landmark);
        current_pose_.position.x() -= 0.01 * err.x();
        current_pose_.position.y() -= 0.01 * err.y();
    }

    // 5. Reset IMU preintegration for next cycle
    imu_->reset();

    return current_pose_;
}

} // namespace auroadas
