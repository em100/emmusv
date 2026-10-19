#include <rclcpp/rclcpp.hpp>

class NodeImpl : public rclcpp::Node
{
public:
    NodeImpl()
    : Node("loop_closure")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "loop_closure node started");
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
