#pragma once

#include <Eigen/Dense>

class IMUPreintegration
{
public:

    IMUPreintegration();

    void integrateMeasurement(
        const Eigen::Vector3d& accel,
        const Eigen::Vector3d& gyro,
        double dt);

    Eigen::Vector3d deltaPosition() const;
    Eigen::Vector3d deltaVelocity() const;

private:

    Eigen::Vector3d delta_p_;
    Eigen::Vector3d delta_v_;

    Eigen::Matrix3d delta_R_;
};