
#include <memory>
#include <rclcpp/rclcpp.hpp>

class DroNetNode : public rclcpp::Node
{
public:
    DroNetNode()
    : Node("dronet_node")
    {
        RCLCPP_INFO(
            get_logger(),
            "AUROUAV DroNet node started");
    }
};


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<DroNetNode>();
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}