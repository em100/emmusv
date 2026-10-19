#include <rclcpp/rclcpp.hpp>

class ControllerNode : public rclcpp::Node
{
public:
    ControllerNode()
    : Node("controller")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Flight Controller Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<ControllerNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}