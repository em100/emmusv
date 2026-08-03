#pragma once
#include <string>

enum class SafetyMode {
    NORMAL,
    CAUTIOUS,
    HOVER,
    EMERGENCY_LAND
};

inline std::string SafetyModeToString(SafetyMode mode) {
    switch (mode) {
        case SafetyMode::NORMAL: return "NORMAL";
        case SafetyMode::CAUTIOUS: return "CAUTIOUS";
        case SafetyMode::HOVER: return "HOVER";
        case SafetyMode::EMERGENCY_LAND: return "EMERGENCY_LAND";
        default: return "UNKNOWN";
    }
}
