#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/float32.hpp>
#include <cv_bridge/cv_bridge.h>

#include "world_model_node.hpp"

class WMNode : public rclcpp::Node {
public:
    WMNode() : Node("world_model_node") {

        img_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/camera/front/image_raw", 10,
            std::bind(&WMNode::imgCallback, this, std::placeholders::_1));

        risk_pub_ = this->create_publisher<std_msgs::msg::Float32>(
            "/world_model/risk", 10);

        steer_pub_ = this->create_publisher<std_msgs::msg::Float32>(
            "/world_model/steering", 10);

        RCLCPP_INFO(this->get_logger(), "WorldModelNode initialized");
    }

private:
    void imgCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
        auto cv = cv_bridge::toCvCopy(msg, "rgb8")->image;

        torch::Tensor input = torch::from_blob(
            cv.data, {1, cv.rows, cv.cols, 3}, torch::kByte
        ).permute({0, 3, 1, 2}).to(torch::kFloat) / 255.0;

        auto z = vit_.forward({input}).toTensor();
        auto z_next = dynamics_.forward({z}).toTensor();

        auto risk = risk_.forward({z_next}).toTensor().item<float>();
        auto steer = steering_.forward({z_next}).toTensor().item<float>();

        std_msgs::msg::Float32 rmsg;
        rmsg.data = risk;
        risk_pub_->publish(rmsg);

        std_msgs::msg::Float32 smsg;
        smsg.data = steer;
        steer_pub_->publish(smsg);
    }

    torch::jit::script::Module vit_, dynamics_, free_space_, risk_, steering_;

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_sub_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr risk_pub_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr steer_pub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<WMNode>());
    rclcpp::shutdown();
    return 0;
}
