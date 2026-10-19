#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>

#include "openvins_interface.hpp"

class OpenVINSInterface : public rclcpp::Node {
public:
    OpenVINSInterface() : Node("vio_frontend") {

        imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/imu/data", 50,
            std::bind(&OpenVINSInterface::imuCallback, this, std::placeholders::_1));

        cam_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/camera/front/image_raw", 10,
            std::bind(&OpenVINSInterface::camCallback, this, std::placeholders::_1));

        vio_pub_ = this->create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>(
            "/vio/pose", 10);

        RCLCPP_INFO(this->get_logger(), "OpenVINS Interface initialized");
    }

private:
    void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg) {
        ov_.feedIMU(msg);
    }

    void camCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
        auto result = ov_.feedCamera(msg);

        if (!result.valid) return;

        geometry_msgs::msg::PoseWithCovarianceStamped out;
        out.header.stamp = msg->header.stamp;
        out.pose = result.pose;
        vio_pub_->publish(out);
    }

    OpenVINSWrapper ov_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr cam_sub_;
    rclcpp::Publisher<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr vio_pub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OpenVINSInterface>());
    rclcpp::shutdown();
    return 0;
}
