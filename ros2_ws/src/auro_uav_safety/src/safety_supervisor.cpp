#include <rclcpp/rclcpp.hpp>

class SafetySupervisorNode : public rclcpp::Node
{
public:
    SafetySupervisorNode()
    : Node("safety_supervisor")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Safety Supervisor Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<SafetySupervisorNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}