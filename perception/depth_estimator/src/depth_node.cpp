#include "depth_estimator.hpp"

using std::placeholders::_1;

namespace auro_uav
{

DepthEstimator::DepthEstimator()
: rclcpp::Node("depth_estimator"),
  caminfo_ready_(false)
{
    // Subscribers
    rgb_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/camera/rgb/image_raw",
        rclcpp::SensorDataQoS(),
        std::bind(&DepthEstimator::rgb_callback, this, _1));

    caminfo_sub_ = this->create_subscription<sensor_msgs::msg::CameraInfo>(
        "/camera/camera_info",
        rclcpp::QoS(10),
        std::bind(&DepthEstimator::caminfo_callback, this, _1));

    // Publisher
    depth_pub_ = this->create_publisher<sensor_msgs::msg::Image>(
        "/auro_uav/depth_map",
        rclcpp::SensorDataQoS());

    RCLCPP_INFO(this->get_logger(), "DepthEstimator node initialized.");
}

void DepthEstimator::caminfo_callback(const sensor_msgs::msg::CameraInfo::SharedPtr msg)
{
    // Build intrinsic matrix K from CameraInfo
    K_ = cv::Mat::zeros(3, 3, CV_64F);
    K_.at<double>(0, 0) = msg->k[0]; // fx
    K_.at<double>(0, 2) = msg->k[2]; // cx
    K_.at<double>(1, 1) = msg->k[4]; // fy
    K_.at<double>(1, 2) = msg->k[5]; // cy
    K_.at<double>(2, 2) = 1.0;

    caminfo_ready_ = true;
    RCLCPP_INFO_ONCE(this->get_logger(), "Camera intrinsics received and stored.");
}

void DepthEstimator::rgb_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    if (!caminfo_ready_) {
        RCLCPP_WARN_THROTTLE(
            this->get_logger(),
            *this->get_clock(),
            2000,
            "CameraInfo not received yet. Skipping depth estimation.");
        return;
    }

    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception &e) {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }

    const cv::Mat &rgb = cv_ptr->image;
    if (rgb.empty()) {
        RCLCPP_ERROR(this->get_logger(), "Received empty RGB image.");
        return;
    }

    // Run depth network
    cv::Mat depth_map = run_depth_network(rgb);

    if (depth_map.empty()) {
        RCLCPP_ERROR(this->get_logger(), "Depth network returned empty output.");
        return;
    }

    auto depth_msg = cv_to_ros(depth_map);
    depth_msg->header = msg->header; // preserve timestamp + frame_id

    depth_pub_->publish(*depth_msg);
}

cv::Mat DepthEstimator::run_depth_network(const cv::Mat &rgb)
{
    // Placeholder implementation:
    // In production, replace this with ONNX/TensorRT inference.
    // For now, we create a fake depth map based on intensity.

    cv::Mat gray, depth;
    cv::cvtColor(rgb, gray, cv::COLOR_BGR2GRAY);
    gray.convertTo(depth, CV_32FC1, 1.0 / 255.0); // normalize to [0,1]

    // Optional: apply a blur to simulate smoother depth
    cv::GaussianBlur(depth, depth, cv::Size(5, 5), 0.0);

    return depth;
}

sensor_msgs::msg::Image::SharedPtr DepthEstimator::cv_to_ros(const cv::Mat &depth_map)
{
    sensor_msgs::msg::Image::SharedPtr msg = std::make_shared<sensor_msgs::msg::Image>();

    msg->height = depth_map.rows;
    msg->width  = depth_map.cols;
    msg->encoding = sensor_msgs::image_encodings::TYPE_32FC1;
    msg->is_bigendian = false;
    msg->step = static_cast<sensor_msgs::msg::Image::_step_type>(
        depth_map.cols * sizeof(float));

    size_t size = msg->step * msg->height;
    msg->data.resize(size);
    std::memcpy(msg->data.data(), depth_map.data, size);

    return msg;
}

} // namespace auro_uav

// --- main entry point ---
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<auro_uav::DepthEstimator>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
