#include <rclcpp/rclcpp.hpp>

class GlobalPlannerNode : public rclcpp::Node
{
public:
    GlobalPlannerNode()
    : Node("global_planner")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Global Planner Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<GlobalPlannerNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}