#include "a_star.hpp"
#include <queue>
#include <cmath>

struct Node {
    int x, y;
    double g, h;
    bool operator>(const Node &other) const { return g + h > other.g + other.h; }
};

std::vector<std::pair<int,int>> AStar::plan(
    const GridMap &map,
    const std::pair<int,int> &start,
    const std::pair<int,int> &goal)
{
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open;
    std::unordered_map<int, double> cost;
    std::unordered_map<int, std::pair<int,int>> parent;

    auto idx = [&](int x, int y){ return y * map.width + x; };

    open.push({start.first, start.second, 0.0, 0.0});
    cost[idx(start.first, start.second)] = 0.0;

    while (!open.empty()) {
        Node cur = open.top();
        open.pop();

        if (cur.x == goal.first && cur.y == goal.second)
            break;

        for (auto &d : neighbors_) {
            int nx = cur.x + d.first;
            int ny = cur.y + d.second;

            if (!map.isFree(nx, ny)) continue;

            double ng = cur.g + 1.0;
            int nidx = idx(nx, ny);

            if (!cost.count(nidx) || ng < cost[nidx]) {
                cost[nidx] = ng;
                double h = std::hypot(goal.first - nx, goal.second - ny);
                open.push({nx, ny, ng, h});
                parent[nidx] = {cur.x, cur.y};
            }
        }
    }

    // reconstruct path
    std::vector<std::pair<int,int>> path;
    std::pair<int,int> cur = goal;

    while (cur != start) {
        path.push_back(cur);
        cur = parent[idx(cur.first, cur.second)];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}
