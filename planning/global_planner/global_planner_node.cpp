#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/path.hpp>
#include "a_star.hpp"
#include "d_star.hpp"

class GlobalPlannerNode : public rclcpp::Node {
public:
    GlobalPlannerNode() : Node("global_planner") {

        this->declare_parameter("algorithm", "A*");
        this->declare_parameter("inflation_radius", 0.5);

        algorithm_ = this->get_parameter("algorithm").as_string();

        map_sub_ = this->create_subscription<nav_msgs::msg::OccupancyGrid>(
            "/global_map", 10,
            std::bind(&GlobalPlannerNode::mapCallback, this, std::placeholders::_1));

        goal_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
            "/goal", 10,
            std::bind(&GlobalPlannerNode::goalCallback, this, std::placeholders::_1));

        path_pub_ = this->create_publisher<nav_msgs::msg::Path>("/global_path", 10);
    }

private:
    void mapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
        map_ = *msg;
    }

    void goalCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
        if (!map_.data.size()) return;

        std::pair<int,int> start = {map_.info.width/2, map_.info.height/2};
        std::pair<int,int> goal = {
            int((msg->pose.position.x - map_.info.origin.position.x) / map_.info.resolution),
            int((msg->pose.position.y - map_.info.origin.position.y) / map_.info.resolution)
        };

        std::vector<std::pair<int,int>> path;

        if (algorithm_ == "A*") {
            AStar planner;
            path = planner.plan(GridMap(map_), start, goal);
        } else {
            DStar planner;
            path = planner.computePath();
        }

        nav_msgs::msg::Path ros_path;
        ros_path.header.frame_id = "map";

        for (auto &p : path) {
            geometry_msgs::msg::PoseStamped pose;
            pose.pose.position.x = p.first * map_.info.resolution;
            pose.pose.position.y = p.second * map_.info.resolution;
            ros_path.poses.push_back(pose);
        }

        path_pub_->publish(ros_path);
    }

    std::string algorithm_;
    nav_msgs::msg::OccupancyGrid map_;

    rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr map_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr goal_sub_;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GlobalPlannerNode>());
    rclcpp::shutdown();
    return 0;
}
