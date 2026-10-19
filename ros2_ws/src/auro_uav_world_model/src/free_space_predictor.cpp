#include <rclcpp/rclcpp.hpp>

class FreeSpacePredictorNode : public rclcpp::Node
{
public:
    FreeSpacePredictorNode()
    : Node("free_space_predictor")
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Free Space Predictor Started");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node =
        std::make_shared<FreeSpacePredictorNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}