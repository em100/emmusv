#include <opencv2/core.hpp>
#include "rclcpp/rclcpp.hpp"

namespace auroadas {

class FeatureExtractor;
class FeatureTracker;

class VisualFrontend {
public:
    VisualFrontend(rclcpp::Node* node)
        : logger_(node->get_logger())
    {
        // In a full implementation, you’d keep these as members
        // and wire them to camera topics.
        RCLCPP_INFO(logger_, "VisualFrontend initialized");
    }

    void processFrame(const cv::Mat& image) {
        // Placeholder: in real code, you’d:
        // 1) Extract features
        // 2) Track features across frames
        // 3) Emit visual factors / measurements
        RCLCPP_INFO(logger_, "VisualFrontend: processing frame (%dx%d)",
                    image.cols, image.rows);
    }

private:
    rclcpp::Logger logger_;
};

} // namespace auroadas
