#include "visual_odometry.hpp"

VisualOdometry::VisualOdometry(
    const cv::Mat& K)
    : K_(K.clone())
{
    orb_ = cv::ORB::create(2000);

    R_ = cv::Mat::eye(3,3,CV_64F);
    t_ = cv::Mat::zeros(3,1,CV_64F);
}

bool VisualOdometry::estimateMotion(
    const cv::Mat& prev_img,
    const cv::Mat& curr_img)
{
    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat des1, des2;

    orb_->detectAndCompute(
        prev_img,
        cv::Mat(),
        kp1,
        des1);

    orb_->detectAndCompute(
        curr_img,
        cv::Mat(),
        kp2,
        des2);

    cv::BFMatcher matcher(
        cv::NORM_HAMMING);

    std::vector<cv::DMatch> matches;

    matcher.match(
        des1,
        des2,
        matches);

    std::vector<cv::Point2f> pts1;
    std::vector<cv::Point2f> pts2;

    for(const auto& m : matches)
    {
        pts1.push_back(
            kp1[m.queryIdx].pt);

        pts2.push_back(
            kp2[m.trainIdx].pt);
    }

    if(pts1.size() < 8)
        return false;

    cv::Mat E =
        cv::findEssentialMat(
            pts1,
            pts2,
            K_);

    cv::recoverPose(
        E,
        pts1,
        pts2,
        K_,
        R_,
        t_);

    return true;
}