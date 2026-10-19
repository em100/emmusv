#include <rclcpp/rclcpp.hpp>

class MPCControllerNode : public rclcpp::Node
{
public:
    MPCControllerNode()
    : Node("mpc_controller")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "MPC Controller Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<MPCControllerNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}