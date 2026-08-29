#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "auroadas/imu_driver.hpp"

namespace auroadas {

ImuDriver::ImuDriver(rclcpp::Node* node)
    : logger_(node->get_logger())
{
    pub_ = node->create_publisher<sensor_msgs::msg::Imu>("/imu/data", 10);

    timer_ = node->create_wall_timer(
        std::chrono::milliseconds(10),   // 100 Hz IMU
        std::bind(&ImuDriver::publishDummyImu, this)
    );

    RCLCPP_INFO(logger_, "ImuDriver started");
}

void ImuDriver::publishDummyImu() {
    sensor_msgs::msg::Imu msg;

    msg.header.stamp = rclcpp::Clock().now();
    msg.header.frame_id = "imu_link";

    msg.angular_velocity.x = 0.0;
    msg.angular_velocity.y = 0.0;
    msg.angular_velocity.z = 0.0;

    msg.linear_acceleration.x = 0.0;
    msg.linear_acceleration.y = 0.0;
    msg.linear_acceleration.z = 9.81;

    pub_->publish(msg);
}

} // namespace auroadas
