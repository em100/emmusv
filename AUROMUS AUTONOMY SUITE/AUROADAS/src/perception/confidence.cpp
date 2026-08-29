#include "rclcpp/rclcpp.hpp"
#include "auroadas/confidence.hpp"

namespace auroadas {

ConfidenceEstimator::ConfidenceEstimator(rclcpp::Logger logger)
    : logger_(logger)
{
    RCLCPP_INFO(logger_, "ConfidenceEstimator initialized");
}

double ConfidenceEstimator::compute(
        const FusionStatus& fusion_status,
        const std::vector<Detection>& detections,
        const TrackingStatus& tracking_status)
{
    double score = 1.0;

    // -----------------------------
    // 1. Localization Confidence
    // -----------------------------
    double loc_conf = computeLocalizationConfidence(fusion_status);
    score *= loc_conf;

    // -----------------------------
    // 2. Detection Confidence
    // -----------------------------
    double det_conf = computeDetectionConfidence(detections);
    score *= det_conf;

    // -----------------------------
    // 3. Tracking Confidence
    // -----------------------------
    double trk_conf = computeTrackingConfidence(tracking_status);
    score *= trk_conf;

    // Clamp to [0,1]
    score = std::max(0.0, std::min(1.0, score));

    RCLCPP_DEBUG(logger_, "ConfidenceEstimator: loc=%.2f det=%.2f trk=%.2f final=%.2f",
                 loc_conf, det_conf, trk_conf, score);

    return score;
}

// ---------------------------------------------------------
// Localization confidence: based on covariance & sensor health
// ---------------------------------------------------------
double ConfidenceEstimator::computeLocalizationConfidence(
        const FusionStatus& fusion_status)
{
    // Example: covariance trace → confidence
    double trace = fusion_status.pose_cov_trace;

    if (trace < 0.1) return 1.0;      // excellent
    if (trace < 0.5) return 0.8;      // good
    if (trace < 1.0) return 0.5;      // degraded
    return 0.2;                       // poor
}

// ---------------------------------------------------------
// Detection confidence: average detection confidence
// ---------------------------------------------------------
double ConfidenceEstimator::computeDetectionConfidence(
        const std::vector<Detection>& detections)
{
    if (detections.empty()) {
        return 0.5; // neutral when no detections
    }

    double sum = 0.0;
    for (const auto& d : detections) {
        sum += d.confidence;
    }

    return std::min(1.0, sum / detections.size());
}

// ---------------------------------------------------------
// Tracking confidence: based on track stability
// ---------------------------------------------------------
double ConfidenceEstimator::computeTrackingConfidence(
        const TrackingStatus& status)
{
    if (status.num_tracks == 0) {
        return 0.5; // neutral
    }

    // Example: ratio of stable tracks
    double ratio = static_cast<double>(status.stable_tracks) /
                   static_cast<double>(status.num_tracks);

    return std::min(1.0, ratio);
}

} // namespace auroadas
