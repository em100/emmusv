#pragma once
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

namespace auroadas {

class CameraDriver {
public:
    CameraDriver(rclcpp::Node* node);
    void start();

private:
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Logger logger_;

    void publishDummyImage();
};

} // namespace auroadas
