#include <rclcpp/rclcpp.hpp>

class NodeImpl : public rclcpp::Node
{
public:
    NodeImpl()
    : Node("pose_graph")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "pose_graph node started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<NodeImpl>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
