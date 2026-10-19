#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <nav_msgs/msg/path.hpp>

#include "mpc_controller.hpp"
#include "bayesian_rl_prior.hpp"

class LocalPlannerNode : public rclcpp::Node {
public:
    LocalPlannerNode() : Node("local_planner") {

        this->declare_parameter("mpc_horizon", 15);
        this->declare_parameter("mpc_dt", 0.1);
        this->declare_parameter("risk_weight", 0.4);

        int horizon = this->get_parameter("mpc_horizon").as_int();
        double dt = this->get_parameter("mpc_dt").as_double();
        risk_weight_ = this->get_parameter("risk_weight").as_double();

        mpc_ = std::make_shared<MPCController>(horizon, dt);

        dronet_sub_ = this->create_subscription<dronet_perception::msg::DronetCommand>(
            "/dronet/command", 10,
            std::bind(&LocalPlannerNode::dronetCallback, this, std::placeholders::_1));

        traj_pub_ = this->create_publisher<nav_msgs::msg::Path>("/local_trajectory", 10);
    }

private:
    void dronetCallback(const dronet_perception::msg::DronetCommand::SharedPtr msg) {

        double steering_prior = BayesianRLPrior::compute(msg->steering, msg->collision_prob);

        State x0{0.0, 0.0};
        std::vector<Waypoint> ref; // empty for now

        Trajectory traj = mpc_->solve(x0, ref, steering_prior, risk_weight_);

        nav_msgs::msg::Path ros_path;
        ros_path.header.frame_id = "map";

        for (auto &p : traj.points) {
            geometry_msgs::msg::PoseStamped pose;
            pose.pose.position.x = p.x;
            pose.pose.position.y = p.y;
            ros_path.poses.push_back(pose);
        }

        traj_pub_->publish(ros_path);
    }

    double risk_weight_;
    std::shared_ptr<MPCController> mpc_;

    rclcpp::Subscription<dronet_perception::msg::DronetCommand>::SharedPtr dronet_sub_;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr traj_pub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LocalPlannerNode>());
    rclcpp::shutdown();
    return 0;
}
