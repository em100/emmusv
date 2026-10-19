#pragma once
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/float32.hpp>
#include <dronet_perception/msg/dronet_command.hpp>

class WorldModelNode {
public:
    WorldModelNode();

    void processImage(const sensor_msgs::msg::Image &img);
    void publishOutputs();

private:
    torch::jit::script::Module vit_;
    torch::jit::script::Module dynamics_;
    torch::jit::script::Module free_space_;
    torch::jit::script::Module risk_;
    torch::jit::script::Module steering_;

    torch::Tensor z_t_;
};
