#include "factor_graph.hpp"
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>

void FactorGraphBackend::addIMUFactor(const IMUPreintegration &imu, int i, int j) {
    graph_.add(gtsam::BetweenFactor<gtsam::Pose3>(
        gtsam::Symbol('x', i),
        gtsam::Symbol('x', j),
        imu.deltaPose(),
        imu_noise_));
}

void FactorGraphBackend::addVIOFactor(const gtsam::Pose3 &pose, int i) {
    graph_.add(gtsam::PriorFactor<gtsam::Pose3>(
        gtsam::Symbol('x', i),
        pose,
        vio_noise_));
}

void FactorGraphBackend::addLoopClosure(const gtsam::Pose3 &rel_pose, int i, int j) {
    graph_.add(gtsam::BetweenFactor<gtsam::Pose3>(
        gtsam::Symbol('x', i),
        gtsam::Symbol('x', j),
        rel_pose,
        lc_noise_));
}

gtsam::Values FactorGraphBackend::optimize() {
    gtsam::LevenbergMarquardtOptimizer optimizer(graph_, values_);
    return optimizer.optimize();
}
