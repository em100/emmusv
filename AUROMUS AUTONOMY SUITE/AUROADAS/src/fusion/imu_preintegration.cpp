#include "auroadas/imu_preintegration.hpp"
#include <rclcpp/rclcpp.hpp>

namespace auroadas {

ImuPreintegration::ImuPreintegration(rclcpp::Logger logger)
    : logger_(logger)
{
    RCLCPP_INFO(logger_, "ImuPreintegration initialized");
    reset();
}

void ImuPreintegration::reset() {
    delta_p_.setZero();
    delta_v_.setZero();
    delta_q_.setIdentity();
}

void ImuPreintegration::integrate(const Eigen::Vector3d& accel,
                                  const Eigen::Vector3d& gyro,
                                  double dt)
{
    // Very simplified IMU integration (placeholder)
    Eigen::Vector3d acc_world = delta_q_ * accel;

    delta_p_ += delta_v_ * dt + 0.5 * acc_world * dt * dt;
    delta_v_ += acc_world * dt;

    Eigen::Quaterniond dq(1.0,
                          0.5 * gyro.x() * dt,
                          0.5 * gyro.y() * dt,
                          0.5 * gyro.z() * dt);
    delta_q_ = (delta_q_ * dq).normalized();
}

Eigen::Vector3d ImuPreintegration::deltaP() const { return delta_p_; }
Eigen::Vector3d ImuPreintegration::deltaV() const { return delta_v_; }
Eigen::Quaterniond ImuPreintegration::deltaQ() const { return delta_q_; }

} // namespace auroadas
