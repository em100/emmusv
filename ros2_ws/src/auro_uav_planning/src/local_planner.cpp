#include <rclcpp/rclcpp.hpp>

class LocalPlannerNode : public rclcpp::Node
{
public:
    LocalPlannerNode()
    : Node("local_planner")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Local Planner Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<LocalPlannerNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}