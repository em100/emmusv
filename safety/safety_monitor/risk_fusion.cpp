#include "risk_fusion.hpp"
#include "safety_modes.hpp"

SafetyMode RiskFusion::computeMode(
    double collision_prob,
    double slam_conf,
    double world_risk,
    double collision_stop_threshold,
    double slam_low_conf_threshold,
    double emergency_land_risk)
{
    // Emergency landing
    if (world_risk >= emergency_land_risk) {
        return SafetyMode::EMERGENCY_LAND;
    }

    // Stop due to collision
    if (collision_prob >= collision_stop_threshold) {
        return SafetyMode::HOVER;
    }

    // SLAM uncertainty
    if (slam_conf <= slam_low_conf_threshold) {
        return SafetyMode::CAUTIOUS;
    }

    // Normal operation
    return SafetyMode::NORMAL;
}
