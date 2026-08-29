#include "rclcpp/rclcpp.hpp"

void log_banner(const rclcpp::Logger& logger) {
    RCLCPP_INFO(logger, "=== AUROADAS: Multi-Sensor Localization & Perception ===");
}
