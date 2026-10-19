#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/geometry/Pose3.h>

class PoseGraphOptimizer
{
public:

    void addConstraint(
        size_t from,
        size_t to,
        const gtsam::Pose3& T)
    {
        graph_.add(
            gtsam::BetweenFactor<
                gtsam::Pose3>(
                    from,
                    to,
                    T,
                    noise_));
    }

private:

    gtsam::NonlinearFactorGraph graph_;
    gtsam::Values values_;

    gtsam::SharedNoiseModel noise_;
};