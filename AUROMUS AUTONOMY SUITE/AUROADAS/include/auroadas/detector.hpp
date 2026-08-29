#pragma once
#include <vector>
#include <Eigen/Dense>

namespace auroadas {

struct Detection {
    Eigen::Vector3d position;
    double confidence;
};

class Detector {
public:
    std::vector<Detection> detect();
};

} // namespace auroadas
