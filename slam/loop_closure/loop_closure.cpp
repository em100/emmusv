#include <opencv2/opencv.hpp>

class LoopClosureDetector
{
public:

    bool detectLoop(
        const cv::Mat& query_desc,
        const cv::Mat& map_desc)
    {
        cv::BFMatcher matcher(
            cv::NORM_HAMMING);

        std::vector<cv::DMatch> matches;

        matcher.match(
            query_desc,
            map_desc,
            matches);

        return matches.size() > 100;
    }
};