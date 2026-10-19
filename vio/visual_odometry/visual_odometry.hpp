#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class VisualOdometry
{
public:

    VisualOdometry(
        const cv::Mat& K);

    bool estimateMotion(
        const cv::Mat& prev_img,
        const cv::Mat& curr_img);

    cv::Mat getRotation() const;
    cv::Mat getTranslation() const;

private:

    cv::Mat K_;

    cv::Mat R_;
    cv::Mat t_;

    cv::Ptr<cv::ORB> orb_;

    std::vector<cv::Point2f>
    extractMatches(
        const cv::Mat& img1,
        const cv::Mat& img2,
        std::vector<cv::Point2f>& pts2);
};