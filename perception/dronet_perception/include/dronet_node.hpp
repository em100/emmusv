#pragma once
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <dronet_perception/msg/dronet_command.hpp>
#include <cv_bridge/cv_bridge.h>

#include "inference_engine.hpp"

class DronetNode : public rclcpp::Node {
public:
    DronetNode();

private:
    void imgCallback(const sensor_msgs::msg::Image::SharedPtr msg);

    std::unique_ptr<InferenceEngine> engine_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_sub_;
    rclcpp::Publisher<dronet_perception::msg::DronetCommand>::SharedPtr cmd_pub_;
};
