#include "auroadas/mapper.hpp"

namespace auroadas {

void Mapper::update(const Pose& pose, const std::vector<MapPoint>& points) {
    map_.insert(map_.end(), points.begin(), points.end());
}

std::vector<MapPoint> Mapper::getLocalMap() const {
    return map_;
}

} // namespace auroadas
