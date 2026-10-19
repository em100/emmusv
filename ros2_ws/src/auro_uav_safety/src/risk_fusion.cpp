#include <rclcpp/rclcpp.hpp>

class RiskFusionNode : public rclcpp::Node
{
public:
    RiskFusionNode()
    : Node("risk_fusion")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Risk Fusion Node Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<RiskFusionNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}