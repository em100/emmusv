#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <dronet_perception/msg/dronet_command.hpp>

class PX4Controller : public rclcpp::Node {
public:
    PX4Controller() : Node("px4_controller") {

        this->declare_parameter("max_forward_speed", 1.0);
        this->declare_parameter("max_yaw_rate", 1.2);
        this->declare_parameter("collision_stop_threshold", 0.9);
        this->declare_parameter("alpha", 0.3);

        max_forward_speed_ = this->get_parameter("max_forward_speed").as_double();
        max_yaw_rate_ = this->get_parameter("max_yaw_rate").as_double();
        collision_stop_threshold_ = this->get_parameter("collision_stop_threshold").as_double();
        alpha_ = this->get_parameter("alpha").as_double();

        v_prev_ = 0.0;

        cmd_pub_ = this->create_publisher<geometry_msgs::msg::Twist>(
            "/aurora/cmd_vel", 10);

        dronet_sub_ = this->create_subscription<dronet_perception::msg::DronetCommand>(
            "/dronet/command", 10,
            std::bind(&PX4Controller::dronetCallback, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "PX4Controller initialized");
    }

private:
    void dronetCallback(const dronet_perception::msg::DronetCommand::SharedPtr msg) {
        float steer = msg->steering;
        float collision = msg->collision_prob;

        geometry_msgs::msg::Twist vel;

        // STOP if collision probability is high
        if (collision >= collision_stop_threshold_) {
            vel.linear.x = 0.0;
            vel.angular.z = steer * 0.0;  // pivot disabled for safety
            cmd_pub_->publish(vel);
            return;
        }

        // Forward velocity modulation
        float v_k = (1.0 - alpha_) * v_prev_ +
                    alpha_ * (1.0 - collision) * max_forward_speed_;

        v_prev_ = v_k;

        vel.linear.x = v_k;
        vel.angular.z = steer * max_yaw_rate_;

        cmd_pub_->publish(vel);
    }

    double max_forward_speed_, max_yaw_rate_, collision_stop_threshold_, alpha_;
    double v_prev_;

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub_;
    rclcpp::Subscription<dronet_perception::msg::DronetCommand>::SharedPtr dronet_sub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PX4Controller>());
    rclcpp::shutdown();
    return 0;
}
