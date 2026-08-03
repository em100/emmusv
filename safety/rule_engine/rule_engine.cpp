#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <geometry_msgs/msg/twist.hpp>

#include "safety_modes.hpp"

class RuleEngine : public rclcpp::Node {
public:
    RuleEngine() : Node("rule_engine") {

        safety_sub_ = this->create_subscription<std_msgs::msg::String>(
            "/aurora/safety_mode", 10,
            std::bind(&RuleEngine::safetyCallback, this, std::placeholders::_1));

        cmd_pub_ = this->create_publisher<geometry_msgs::msg::Twist>(
            "/aurora/cmd_vel", 10);

        RCLCPP_INFO(this->get_logger(), "RuleEngine initialized");
    }

private:
    void safetyCallback(const std_msgs::msg::String::SharedPtr msg) {
        geometry_msgs::msg::Twist cmd;

        if (msg->data == "NORMAL") {
            return; // let PX4Controller handle normal motion
        }

        if (msg->data == "CAUTIOUS") {
            cmd.linear.x = 0.2;
            cmd.angular.z = 0.0;
        }

        if (msg->data == "HOVER") {
            cmd.linear.x = 0.0;
            cmd.angular.z = 0.0;
        }

        if (msg->data == "EMERGENCY_LAND") {
            cmd.linear.z = -0.5; // descend
        }

        cmd_pub_->publish(cmd);
    }

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr safety_sub_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RuleEngine>());
    rclcpp::shutdown();
    return 0;
}
