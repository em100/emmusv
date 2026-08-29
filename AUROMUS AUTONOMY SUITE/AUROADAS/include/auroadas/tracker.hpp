#pragma once
#include <vector>
#include "detector.hpp"

namespace auroadas {

class Tracker {
public:
    void update(const std::vector<Detection>& detections);
};

} // namespace auroadas
