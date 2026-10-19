#include <rclcpp/rclcpp.hpp>

class LatentDynamicsNode : public rclcpp::Node
{
public:
    LatentDynamicsNode()
    : Node("latent_dynamics")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Latent Dynamics Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<LatentDynamicsNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}