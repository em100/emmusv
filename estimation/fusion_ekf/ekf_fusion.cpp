#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>
#include <sensor_msgs/msg/imu.hpp>

#include "ekf_fusion.hpp"

class EKFFusionNode : public rclcpp::Node {
public:
    EKFFusionNode() : Node("ekf_fusion") {

        this->declare_parameter("process_noise", 0.01);
        this->declare_parameter("measurement_noise", 0.05);

        ekf_.setProcessNoise(this->get_parameter("process_noise").as_double());
        ekf_.setMeasurementNoise(this->get_parameter("measurement_noise").as_double());

        imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/imu/data", 50,
            std::bind(&EKFFusionNode::imuCallback, this, std::placeholders::_1));

        vio_sub_ = this->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
            "/vio/pose", 10,
            std::bind(&EKFFusionNode::vioCallback, this, std::placeholders::_1));

        slam_sub_ = this->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
            "/slam/pose", 10,
            std::bind(&EKFFusionNode::slamCallback, this, std::placeholders::_1));

        fused_pub_ = this->create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>(
            "/state/pose", 10);

        RCLCPP_INFO(this->get_logger(), "EKF Fusion initialized");
    }

private:
    void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg) {
        ekf_.predict(*msg);
    }

    void vioCallback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg) {
        ekf_.updateVIO(*msg);
        publishState(msg->header.stamp);
    }

    void slamCallback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg) {
        ekf_.updateSLAM(*msg);
        publishState(msg->header.stamp);
    }

    void publishState(const rclcpp::Time &stamp) {
        auto out = ekf_.getState();
        out.header.stamp = stamp;
        fused_pub_->publish(out);
    }

    EKFFusion ekf_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr vio_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr slam_sub_;
    rclcpp::Publisher<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr fused_pub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<EKFFusionNode>());
    rclcpp::shutdown();
    return 0;
}
