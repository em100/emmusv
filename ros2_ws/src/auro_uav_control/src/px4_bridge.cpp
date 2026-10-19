#include <rclcpp/rclcpp.hpp>

class PX4BridgeNode : public rclcpp::Node
{
public:
    PX4BridgeNode()
    : Node("px4_bridge")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "PX4 Bridge Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<PX4BridgeNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}