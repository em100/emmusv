#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <dronet_perception/msg/dronet_command.hpp>
#include <std_msgs/msg/float32.hpp>

#include "risk_fusion.hpp"
#include "safety_modes.hpp"

class SafetyNode : public rclcpp::Node {
public:
    SafetyNode() : Node("safety_monitor") {

        this->declare_parameter("collision_stop_threshold", 0.9);
        this->declare_parameter("slam_low_confidence_threshold", 0.3);
        this->declare_parameter("emergency_land_risk", 0.8);

        collision_stop_threshold_ = this->get_parameter("collision_stop_threshold").as_double();
        slam_low_confidence_threshold_ = this->get_parameter("slam_low_confidence_threshold").as_double();
        emergency_land_risk_ = this->get_parameter("emergency_land_risk").as_double();

        dronet_sub_ = this->create_subscription<dronet_perception::msg::DronetCommand>(
            "/dronet/command", 10,
            std::bind(&SafetyNode::dronetCallback, this, std::placeholders::_1));

        slam_conf_sub_ = this->create_subscription<std_msgs::msg::Float32>(
            "/slam/confidence", 10,
            std::bind(&SafetyNode::slamConfCallback, this, std::placeholders::_1));

        risk_sub_ = this->create_subscription<std_msgs::msg::Float32>(
            "/world_model/risk", 10,
            std::bind(&SafetyNode::riskCallback, this, std::placeholders::_1));

        safety_pub_ = this->create_publisher<std_msgs::msg::String>(
            "/aurora/safety_mode", 10);

        RCLCPP_INFO(this->get_logger(), "SafetyNode initialized");
    }

private:
    void dronetCallback(const dronet_perception::msg::DronetCommand::SharedPtr msg) {
        collision_prob_ = msg->collision_prob;
        evaluateSafety();
    }

    void slamConfCallback(const std_msgs::msg::Float32::SharedPtr msg) {
        slam_confidence_ = msg->data;
        evaluateSafety();
    }

    void riskCallback(const std_msgs::msg::Float32::SharedPtr msg) {
        world_risk_ = msg->data;
        evaluateSafety();
    }

    void evaluateSafety() {
        SafetyMode mode = RiskFusion::computeMode(
            collision_prob_,
            slam_confidence_,
            world_risk_,
            collision_stop_threshold_,
            slam_low_confidence_threshold_,
            emergency_land_risk_
        );

        std_msgs::msg::String out;
        out.data = SafetyModeToString(mode);
        safety_pub_->publish(out);
    }

    double collision_prob_{0.0};
    double slam_confidence_{1.0};
    double world_risk_{0.0};

    double collision_stop_threshold_;
    double slam_low_confidence_threshold_;
    double emergency_land_risk_;

    rclcpp::Subscription<dronet_perception::msg::DronetCommand>::SharedPtr dronet_sub_;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr slam_conf_sub_;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr risk_sub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr safety_pub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SafetyNode>());
    rclcpp::shutdown();
    return 0;
}
