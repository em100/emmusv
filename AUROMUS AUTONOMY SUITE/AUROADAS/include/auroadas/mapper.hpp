#pragma once
#include <vector>
#include <Eigen/Dense>
#include "fusion_graph.hpp"

namespace auroadas {

struct MapPoint {
    Eigen::Vector3d position;
};

class Mapper {
public:
    void update(const Pose& pose, const std::vector<MapPoint>& points);
    std::vector<MapPoint> getLocalMap() const;

private:
    std::vector<MapPoint> map_;
};

} // namespace auroadas
