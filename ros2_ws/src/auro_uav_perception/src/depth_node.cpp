#include <rclcpp/rclcpp.hpp>

class DepthNode : public rclcpp::Node
{
public:
    DepthNode()
        : Node("depth_node")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Depth Estimator Node Started");
    }
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);

    auto node =
        std::make_shared<DepthNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}