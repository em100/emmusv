#include <rclcpp/rclcpp.hpp>

class SemanticSegmentationNode : public rclcpp::Node
{
public:
    SemanticSegmentationNode()
        : Node("semantic_segmentation_node")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Semantic Segmentation Node Started");
    }
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);

    auto node =
        std::make_shared<SemanticSegmentationNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}