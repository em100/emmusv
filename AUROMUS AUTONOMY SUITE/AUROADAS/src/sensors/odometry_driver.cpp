#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "auroadas/odometry_driver.hpp"

namespace auroadas {

OdometryDriver::OdometryDriver(rclcpp::Node* node)
    : logger_(node->get_logger())
{
    pub_ = node->create_publisher<nav_msgs::msg::Odometry>("/vehicle/odometry", 10);

    timer_ = node->create_wall_timer(
        std::chrono::milliseconds(50),   // 20 Hz wheel odometry
        std::bind(&OdometryDriver::publishDummyOdom, this)
    );

    RCLCPP_INFO(logger_, "OdometryDriver started");
}

void OdometryDriver::publishDummyOdom() {
    nav_msgs::msg::Odometry msg;

    msg.header.stamp = rclcpp::Clock().now();
    msg.header.frame_id = "odom";

    msg.pose.pose.position.x = 0.0;
    msg.pose.pose.position.y = 0.0;
    msg.pose.pose.position.z = 0.0;

    msg.twist.twist.linear.x = 0.0;
    msg.twist.twist.angular.z = 0.0;

    pub_->publish(msg);
}

} // namespace auroadas
