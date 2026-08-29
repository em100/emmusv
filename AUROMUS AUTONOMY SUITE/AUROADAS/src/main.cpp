#include <rclcpp/rclcpp.hpp>

#include "auroadas/camera_driver.hpp"
#include "auroadas/fusion_graph.hpp"
#include "auroadas/mapper.hpp"
#include "auroadas/detector.hpp"
#include "auroadas/tracker.hpp"

using namespace auroadas;

class AUROADASNode : public rclcpp::Node {
public:
    AUROADASNode() : Node("auroadas_node") {
        RCLCPP_INFO(get_logger(), "AUROADAS node started");

        // Instantiate modules
        camera_ = std::make_shared<CameraDriver>(this);
        fusion_ = std::make_shared<FusionGraph>();
        mapper_ = std::make_shared<Mapper>();
        detector_ = std::make_shared<Detector>();
        tracker_ = std::make_shared<Tracker>();

        camera_->start();

        // Example timer to simulate pipeline
        timer_ = create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&AUROADASNode::pipelineStep, this));
    }

private:
    std::shared_ptr<CameraDriver> camera_;
    std::shared_ptr<FusionGraph> fusion_;
    std::shared_ptr<Mapper> mapper_;
    std::shared_ptr<Detector> detector_;
    std::shared_ptr<Tracker> tracker_;

    rclcpp::TimerBase::SharedPtr timer_;

    void pipelineStep() {
        Pose pose = fusion_->optimize();
        auto detections = detector_->detect();
        tracker_->update(detections);

        std::vector<MapPoint> dummy_points;
        mapper_->update(pose, dummy_points);
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AUROADASNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
