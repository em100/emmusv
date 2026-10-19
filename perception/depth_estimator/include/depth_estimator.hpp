#ifndef DEPTH_ESTIMATOR_HPP
#define DEPTH_ESTIMATOR_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

namespace auro_uav
{

class DepthEstimator : public rclcpp::Node
{
public:
    DepthEstimator();
    ~DepthEstimator() = default;

private:
    // --- Subscribers ---
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr rgb_sub_;
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr caminfo_sub_;

    // --- Publishers ---
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr depth_pub_;

    // --- Camera intrinsics ---
    cv::Mat K_;          // 3x3 intrinsic matrix
    bool caminfo_ready_; // flag

    // --- Model inference ---
    cv::Mat run_depth_network(const cv::Mat &rgb);

    // --- Callbacks ---
    void rgb_callback(const sensor_msgs::msg::Image::SharedPtr msg);
    void caminfo_callback(const sensor_msgs::msg::CameraInfo::SharedPtr msg);

    // --- Utility ---
    sensor_msgs::msg::Image::SharedPtr cv_to_ros(const cv::Mat &depth_map);
};

} // namespace auro_uav

#endif // DEPTH_ESTIMATOR_HPP
