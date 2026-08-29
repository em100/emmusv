#include "auroadas/camera_driver.hpp"

namespace auroadas {

CameraDriver::CameraDriver(rclcpp::Node* node)
    : logger_(node->get_logger()) 
{
    pub_ = node->create_publisher<sensor_msgs::msg::Image>(
        "/camera/front/image_raw", 10);

    timer_ = node->create_wall_timer(
        std::chrono::milliseconds(33),
        std::bind(&CameraDriver::publishDummyImage, this));
}

void CameraDriver::start() {
    RCLCPP_INFO(logger_, "CameraDriver started");
}

void CameraDriver::publishDummyImage() {
    sensor_msgs::msg::Image img;
    img.height = 480;
    img.width = 640;
    img.encoding = "rgb8";
    img.data.resize(img.height * img.width * 3);
    pub_->publish(img);
}

} // namespace auroadas
