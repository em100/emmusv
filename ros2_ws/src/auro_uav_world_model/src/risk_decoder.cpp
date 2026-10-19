#include <rclcpp/rclcpp.hpp>

class RiskDecoderNode : public rclcpp::Node
{
public:
    RiskDecoderNode()
    : Node("risk_decoder")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Risk Decoder Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<RiskDecoderNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}