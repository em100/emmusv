#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include "rclcpp/rclcpp.hpp"

namespace auroadas {

class FeatureExtractor {
public:
    FeatureExtractor(rclcpp::Logger logger)
        : logger_(logger)
    {
        detector_ = cv::ORB::create(1000);
    }

    std::vector<cv::KeyPoint> extract(const cv::Mat& image, cv::Mat& descriptors) {
        std::vector<cv::KeyPoint> keypoints;
        if (image.empty()) {
            RCLCPP_WARN(logger_, "FeatureExtractor: empty image");
            return keypoints;
        }
        detector_->detectAndCompute(image, cv::noArray(), keypoints, descriptors);
        return keypoints;
    }

private:
    rclcpp::Logger logger_;
    cv::Ptr<cv::Feature2D> detector_;
};

} // namespace auroadas
