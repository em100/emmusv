#include "auroadas/loop_closure.hpp"
#include "auroadas/pose_graph.hpp"
#include <rclcpp/rclcpp.hpp>

namespace auroadas {

LoopClosure::LoopClosure(rclcpp::Logger logger, PoseGraph* graph)
    : logger_(logger), graph_(graph)
{
    RCLCPP_INFO(logger_, "LoopClosure initialized");
}

void LoopClosure::checkForLoop(const Pose& current_pose)
{
    const auto& nodes = graph_->getNodes();

    if (nodes.empty()) return;

    int best_id = -1;
    double best_dist = 9999.0;

    for (int i = 0; i < nodes.size(); i++) {
        double dist = (nodes[i].position - current_pose.position).norm();
        if (dist < best_dist) {
            best_dist = dist;
            best_id = i;
        }
    }

    // Threshold for loop closure detection
    if (best_dist < 1.0) {
        RCLCPP_INFO(logger_, "LoopClosure: detected loop with node %d (dist=%.2f)",
                    best_id, best_dist);

        Eigen::Matrix4d relative = Eigen::Matrix4d::Identity();
        graph_->addEdge(nodes.size() - 1, best_id, relative);
    }
}

} // namespace auroadas
