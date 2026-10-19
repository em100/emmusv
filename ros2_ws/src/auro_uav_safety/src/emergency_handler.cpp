#include <rclcpp/rclcpp.hpp>

class EmergencyHandlerNode : public rclcpp::Node
{
public:
    EmergencyHandlerNode()
    : Node("emergency_handler")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Emergency Handler Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<EmergencyHandlerNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}