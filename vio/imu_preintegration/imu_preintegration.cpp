#include "imu_preintegration.hpp"

IMUPreintegration::IMUPreintegration()
{
    delta_p_.setZero();
    delta_v_.setZero();
    delta_R_.setIdentity();
}

void IMUPreintegration::integrateMeasurement(
    const Eigen::Vector3d& accel,
    const Eigen::Vector3d& gyro,
    double dt)
{
    delta_p_ +=
        delta_v_ * dt +
        0.5 * accel * dt * dt;

    delta_v_ +=
        accel * dt;

    Eigen::AngleAxisd rot(
        gyro.norm() * dt,
        gyro.normalized());

    delta_R_ =
        delta_R_ *
        rot.toRotationMatrix();
}