#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>

#include "factor_graph.hpp"
#include "loop_closure.hpp"

class SLAMNode : public rclcpp::Node {
public:
    SLAMNode() : Node("slam_backend") {

        pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
            "/vio/pose", 10,
            std::bind(&SLAMNode::poseCallback, this, std::placeholders::_1));

        slam_pub_ = this->create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>(
            "/slam/pose", 10);

        RCLCPP_INFO(this->get_logger(), "SLAM Backend initialized");
    }

private:
    void poseCallback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg) {
        Pose p(msg->pose);

        poses_.push_back(p);

        int i = poses_.size() - 1;

        if (i > 0) {
            imu_.integrate(last_imu_, dt_);
            fg_.addIMUFactor(imu_, i - 1, i);
        }

        fg_.addVIOFactor(p.toGTSAM(), i);

        // Loop closure detection
        for (int j = 0; j < i - 20; j++) {
            if (lc_.detect(p, poses_[j])) {
                auto rel = lc_.computeRelativePose(poses_[j], p);
                fg_.addLoopClosure(rel, j, i);
            }
        }

        auto result = fg_.optimize();
        auto optimized_pose = result.at<gtsam::Pose3>(gtsam::Symbol('x', i));

        geometry_msgs::msg::PoseWithCovarianceStamped out;
        out.header.stamp = msg->header.stamp;
        out.pose = Pose::fromGTSAM(optimized_pose);
        slam_pub_->publish(out);
    }

    FactorGraphBackend fg_;
    LoopClosureDetector lc_;
    IMUPreintegration imu_;
    sensor_msgs::msg::Imu last_imu_;
    double dt_{0.01};

    std::vector<Pose> poses_;

    rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr pose_sub_;
    rclcpp::Publisher<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr slam_pub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SLAMNode>());
    rclcpp::shutdown();
    return 0;
}
