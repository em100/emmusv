#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include "local_mapper.hpp"

class LocalMapperNode : public rclcpp::Node {
public:
    LocalMapperNode() : Node("local_mapper") {

        this->declare_parameter("grid_size", 20.0);
        this->declare_parameter("resolution", 0.1);

        double grid_size = this->get_parameter("grid_size").as_double();
        double resolution = this->get_parameter("resolution").as_double();

        mapper_ = std::make_shared<LocalMapper>(grid_size, resolution);

        pc_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/pointcloud", 10,
            std::bind(&LocalMapperNode::pcCallback, this, std::placeholders::_1));

        grid_pub_ = this->create_publisher<nav_msgs::msg::OccupancyGrid>(
            "/local_map", 10);

        RCLCPP_INFO(this->get_logger(), "LocalMapper initialized");
    }

private:
    void pcCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
        mapper_->update(*msg);
        grid_pub_->publish(mapper_->getGrid());
    }

    std::shared_ptr<LocalMapper> mapper_;
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pc_sub_;
    rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr grid_pub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LocalMapperNode>());
    rclcpp::shutdown();
    return 0;
}
