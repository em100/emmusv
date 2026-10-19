#include <rclcpp/rclcpp.hpp>

class ViTEncoderNode : public rclcpp::Node
{
public:
    ViTEncoderNode()
    : Node("vit_encoder")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "ViT Encoder Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<ViTEncoderNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}