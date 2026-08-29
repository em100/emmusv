#include <opencv2/core.hpp>
#include <opencv2/video/tracking.hpp>
#include "rclcpp/rclcpp.hpp"

namespace auroadas {

class FeatureTracker {
public:
    FeatureTracker(rclcpp::Logger logger)
        : logger_(logger)
    {}

    void track(const cv::Mat& prev_img,
               const cv::Mat& curr_img,
               const std::vector<cv::Point2f>& prev_pts,
               std::vector<cv::Point2f>& curr_pts,
               std::vector<unsigned char>& status)
    {
        if (prev_img.empty() || curr_img.empty() || prev_pts.empty()) {
            RCLCPP_WARN(logger_, "FeatureTracker: invalid input");
            return;
        }

        std::vector<float> err;
        cv::calcOpticalFlowPyrLK(prev_img, curr_img, prev_pts, curr_pts, status, err);
    }

private:
    rclcpp::Logger logger_;
};

} // namespace auroadas
