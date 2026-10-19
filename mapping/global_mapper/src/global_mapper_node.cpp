#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>

#include "global_mapper.hpp"

class GlobalMapperNode : public rclcpp::Node {
public:
    GlobalMapperNode() : Node("global_mapper") {

        this->declare_parameter("map_size", 200.0);
        this->declare_parameter("voxel_resolution", 0.2);

        double map_size = this->get_parameter("map_size").as_double();
        double voxel_res = this->get_parameter("voxel_resolution").as_double();

        mapper_ = std::make_shared<GlobalMapper>(map_size, voxel_res);

        pc_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/pointcloud", 10,
            std::bind(&GlobalMapperNode::pcCallback, this, std::placeholders::_1));

        semseg_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/semantic_mask", 10,
            std::bind(&GlobalMapperNode::semsegCallback, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "GlobalMapper initialized");
    }

private:
    void pcCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
        mapper_->update(*msg);
    }

    void semsegCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
        cv::Mat mask = cv_bridge::toCvCopy(msg, "mono8")->image;
        mapper_->updateSemantic(mask);
    }

    std::shared_ptr<GlobalMapper> mapper_;
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pc_sub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr semseg_sub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GlobalMapperNode>());
    rclcpp::shutdown();
    return 0;
}
