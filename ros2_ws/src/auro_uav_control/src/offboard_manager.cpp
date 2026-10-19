#include <rclcpp/rclcpp.hpp>

class OffboardManagerNode : public rclcpp::Node
{
public:
    OffboardManagerNode()
    : Node("offboard_manager")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Offboard Manager Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<OffboardManagerNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}