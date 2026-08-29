
#include "auroadas/pose_graph.hpp"
#include <rclcpp/rclcpp.hpp>

namespace auroadas {

PoseGraph::PoseGraph(rclcpp::Logger logger)
    : logger_(logger)
{
    RCLCPP_INFO(logger_, "PoseGraph initialized");
}

int PoseGraph::addNode(const Pose& pose)
{
    int id = nodes_.size();
    nodes_.push_back(pose);
    RCLCPP_DEBUG(logger_, "PoseGraph: added node %d", id);
    return id;
}

void PoseGraph::addEdge(int from, int to, const Eigen::Matrix4d& relative_pose)
{
    if (from < 0 || to < 0 || from >= nodes_.size() || to >= nodes_.size()) {
        RCLCPP_WARN(logger_, "PoseGraph: invalid edge (%d -> %d)", from, to);
        return;
    }

    edges_.push_back({from, to, relative_pose});
    RCLCPP_DEBUG(logger_, "PoseGraph: added edge %d -> %d", from, to);
}

void PoseGraph::optimize()
{
    // Placeholder: real implementation would call GTSAM or Ceres
    RCLCPP_INFO(logger_, "PoseGraph: optimize() called (stub)");
}

const std::vector<Pose>& PoseGraph::getNodes() const
{
    return nodes_;
}

const std::vector<PoseGraphEdge>& PoseGraph::getEdges() const
{
    return edges_;
}

} // namespace auroadas
