#pragma once
#include <Eigen/Dense>
#include <rclcpp/rclcpp.hpp>

namespace auroadas {

class ImuPreintegration {
public:
    ImuPreintegration(rclcpp::Logger logger);

    void reset();

    void integrate(const Eigen::Vector3d& accel,
                   const Eigen::Vector3d& gyro,
                   double dt);

    Eigen::Vector3d deltaP() const;
    Eigen::Vector3d deltaV() const;
    Eigen::Quaterniond deltaQ() const;

private:
    rclcpp::Logger logger_;

    Eigen::Vector3d delta_p_;
    Eigen::Vector3d delta_v_;
    Eigen::Quaterniond delta_q_;
};

} // namespace auroadas
