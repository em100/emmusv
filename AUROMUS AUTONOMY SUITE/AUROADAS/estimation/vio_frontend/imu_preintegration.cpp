#include "imu_preintegration.hpp"
#include <Eigen/Dense>

IMUPreintegration::IMUPreintegration() {
    reset();
}

void IMUPreintegration::reset() {
    delta_p_.setZero();
    delta_v_.setZero();
    delta_q_.setIdentity();
}

void IMUPreintegration::integrate(const sensor_msgs::msg::Imu &imu, double dt) {
    Eigen::Vector3d acc(imu.linear_acceleration.x,
                        imu.linear_acceleration.y,
                        imu.linear_acceleration.z);

    Eigen::Vector3d gyro(imu.angular_velocity.x,
                         imu.angular_velocity.y,
                         imu.angular_velocity.z);

    // Update orientation
    Eigen::Quaterniond dq(1,
                          0.5 * gyro.x() * dt,
                          0.5 * gyro.y() * dt,
                          0.5 * gyro.z() * dt);
    delta_q_ = (delta_q_ * dq).normalized();

    // Update velocity
    delta_v_ += delta_q_ * acc * dt;

    // Update position
    delta_p_ += delta_v_ * dt + 0.5 * (delta_q_ * acc) * dt * dt;
}
