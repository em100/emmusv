#include "dronet_node.hpp"

DronetNode::DronetNode() : Node("dronet_node") {

    this->declare_parameter("engine_path", "models/dronet_fp16.engine");
    std::string engine_path = this->get_parameter("engine_path").as_string();

    engine_ = std::make_unique<InferenceEngine>(engine_path);

    img_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/camera/front/image_raw", 10,
        std::bind(&DronetNode::imgCallback, this, std::placeholders::_1));

    cmd_pub_ = this->create_publisher<dronet_perception::msg::DronetCommand>(
        "/dronet/command", 10);

    RCLCPP_INFO(this->get_logger(), "DroNet Perception Node initialized");
}

void DronetNode::imgCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
    auto cv = cv_bridge::toCvCopy(msg, "bgr8")->image;

    auto [steer, collision] = engine_->infer(cv);

    dronet_perception::msg::DronetCommand out;
    out.steering = steer;
    out.collision_prob = collision;

    cmd_pub_->publish(out);
}
