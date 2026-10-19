#include "mpc_controller.hpp"
#include <Eigen/Dense>

MPCController::MPCController(int horizon, double dt)
    : N_(horizon), dt_(dt)
{
    A_.setIdentity();
    B_ << dt_, 0,
          0, dt_;
}

Trajectory MPCController::solve(
    const State &x0,
    const std::vector<Waypoint> &ref,
    double steering_prior,
    double risk_weight)
{
    Eigen::Vector2d x = x0.toEigen();
    Trajectory traj;

    for (int i = 0; i < N_; i++) {
        Eigen::Vector2d u;
        u << steering_prior, 1.0 - risk_weight;

        x = A_ * x + B_ * u;

        traj.points.push_back({x(0), x(1)});
    }

    return traj;
}
