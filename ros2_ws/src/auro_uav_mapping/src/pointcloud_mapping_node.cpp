#include <rclcpp/rclcpp.hpp>

class PointCloudMappingNode : public rclcpp::Node
{
public:
    PointCloudMappingNode()
    : Node("pointcloud_mapping_node")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Point Cloud Mapping Node Started");
    }
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);

    auto node =
        std::make_shared<PointCloudMappingNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
