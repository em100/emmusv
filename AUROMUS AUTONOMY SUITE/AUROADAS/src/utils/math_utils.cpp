#include "Eigen/Dense"
#include "rclcpp/rclcpp.hpp"

namespace auroadas {

Eigen::Matrix3d skew(const Eigen::Vector3d& v) {
    Eigen::Matrix3d S;
    S <<     0, -v.z(),  v.y(),
          v.z(),     0, -v.x(),
         -v.y(),  v.x(),     0;
    return S;
}

Eigen::Quaterniond normalizeQuat(const Eigen::Quaterniond& q) {
    Eigen::Quaterniond qn = q;
    qn.normalize();
    return qn;
}

Eigen::Vector3d rotate(const Eigen::Quaterniond& q, const Eigen::Vector3d& v) {
    return q * v;
}

Eigen::Matrix3d quatToRot(const Eigen::Quaterniond& q) {
    return q.toRotationMatrix();
}

} // namespace auroadas
