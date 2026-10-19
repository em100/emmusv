#include <opencv2/opencv.hpp>

class FeatureTracker
{
public:

    FeatureTracker()
    {
        detector_ =
            cv::ORB::create(2500);
    }

    void track(
        const cv::Mat& img,
        std::vector<cv::KeyPoint>& keypoints,
        cv::Mat& descriptors)
    {
        detector_->detectAndCompute(
            img,
            cv::Mat(),
            keypoints,
            descriptors);
    }

private:

    cv::Ptr<cv::ORB> detector_;
};
``