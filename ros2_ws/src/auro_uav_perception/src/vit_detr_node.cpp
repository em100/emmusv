#include <rclcpp/rclcpp.hpp>

class ViTDetrNode : public rclcpp::Node
{
public:
    ViTDetrNode()
        : Node("vit_detr_node")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "ViT-DETR Node Started");
    }
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);

    auto node =
        std::make_shared<ViTDetrNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}