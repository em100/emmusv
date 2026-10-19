#include "loop_closure.hpp"
#include <Eigen/Dense>

bool LoopClosureDetector::detect(const Pose &current, const Pose &candidate) {
    double dist = (current.position - candidate.position).norm();
    return dist < threshold_;
}

gtsam::Pose3 LoopClosureDetector::computeRelativePose(const Pose &a, const Pose &b) {
    Eigen::Vector3d t = b.position - a.position;
    Eigen::Quaterniond q = b.orientation * a.orientation.inverse();
    return gtsam::Pose3(q, t);
}
