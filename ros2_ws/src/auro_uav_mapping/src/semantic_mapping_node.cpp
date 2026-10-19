#include <rclcpp/rclcpp.hpp>

class SemanticMappingNode : public rclcpp::Node
{
public:
    SemanticMappingNode()
    : Node("semantic_mapping_node")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Semantic Mapping Node Started");
    }
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);

    auto node =
        std::make_shared<SemanticMappingNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
