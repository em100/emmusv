#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <mavros_msgs/msg/state.hpp>
#include <mavros_msgs/msg/set_mode.hpp>
#include <mavros_msgs/msg/command_bool.hpp>

class MavlinkBridge : public rclcpp::Node {
public:
    MavlinkBridge() : Node("mavlink_bridge") {

        // Publishers to MAVROS
        vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>(
            "/mavros/setpoint_velocity/cmd_vel_unstamped", 10);

        arm_pub_ = this->create_publisher<mavros_msgs::msg::CommandBool>(
            "/mavros/cmd/arming", 10);

        mode_pub_ = this->create_publisher<mavros_msgs::msg::SetMode>(
            "/mavros/set_mode", 10);

        // Subscribe to AURORA velocity commands
        cmd_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/aurora/cmd_vel", 10,
            std::bind(&MavlinkBridge::cmdCallback, this, std::placeholders::_1));

        // Subscribe to PX4 state
        state_sub_ = this->create_subscription<mavros_msgs::msg::State>(
            "/mavros/state", 10,
            std::bind(&MavlinkBridge::stateCallback, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "MavlinkBridge initialized");
    }

private:
    void cmdCallback(const geometry_msgs::msg::Twist::SharedPtr msg) {
        vel_pub_->publish(*msg);
    }

    void stateCallback(const mavros_msgs::msg::State::SharedPtr msg) {
        if (!msg->armed) {
            mavros_msgs::msg::CommandBool arm_cmd;
            arm_cmd.value = true;
            arm_pub_->publish(arm_cmd);
        }

        if (msg->mode != "OFFBOARD") {
            mavros_msgs::msg::SetMode mode_cmd;
            mode_cmd.custom_mode = "OFFBOARD";
            mode_pub_->publish(mode_cmd);
        }
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub_;
    rclcpp::Publisher<mavros_msgs::msg::CommandBool>::SharedPtr arm_pub_;
    rclcpp::Publisher<mavros_msgs::msg::SetMode>::SharedPtr mode_pub_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_sub_;
    rclcpp::Subscription<mavros_msgs::msg::State>::SharedPtr state_sub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MavlinkBridge>());
    rclcpp::shutdown();
    return 0;
}
