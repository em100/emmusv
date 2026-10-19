#include <rclcpp/rclcpp.hpp>

class OccupancyGridNode : public rclcpp::Node
{
public:
    OccupancyGridNode()
    : Node("occupancy_grid_node")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Occupancy Grid Node Started");
    }
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);

    auto node =
        std::make_shared<OccupancyGridNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
