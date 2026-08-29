#include "bayesian_rl_prior.hpp"
#include <cmath>

double BayesianRLPrior::compute(double steering_pred, double collision_prob) {

    double prior_var = 0.1 + collision_prob * 0.5;
    double weight = std::exp(-prior_var);

    return steering_pred * weight;
}
