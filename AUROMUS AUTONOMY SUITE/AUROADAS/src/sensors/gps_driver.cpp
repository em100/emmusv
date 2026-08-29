#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/nav_sat_fix.hpp"
#include "auroadas/gps_driver.hpp"

namespace auroadas {

GpsDriver::GpsDriver(rclcpp::Node* node)
    : logger_(node->get_logger())
{
    pub_ = node->create_publisher<sensor_msgs::msg::NavSatFix>("/gps/fix", 10);

    timer_ = node->create_wall_timer(
        std::chrono::milliseconds(200),   // 5 Hz GPS
        std::bind(&GpsDriver::publishDummyGps, this)
    );

    RCLCPP_INFO(logger_, "GpsDriver started");
}

void GpsDriver::publishDummyGps() {
    sensor_msgs::msg::NavSatFix msg;

    msg.header.stamp = rclcpp::Clock().now();
    msg.header.frame_id = "gps_link";

    msg.latitude = 37.7749;   // dummy SF coordinates
    msg.longitude = -122.4194;
    msg.altitude = 10.0;

    msg.status.status = sensor_msgs::msg::NavSatStatus::STATUS_FIX;
    msg.status.service = sensor_msgs::msg::NavSatStatus::SERVICE_GPS;

    pub_->publish(msg);
}

} // namespace auroadas
