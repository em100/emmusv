#include "d_star.hpp"
#include <queue>
#include <cmath>

double DStar::heuristic(const Cell &a, const Cell &b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}

void DStar::updateVertex(Cell &u) {
    if (!u.isObstacle) {
        double min_rhs = INF;
        for (auto &nbr : neighbors(u)) {
            min_rhs = std::min(min_rhs, nbr.g + cost(u, nbr));
        }
        u.rhs = min_rhs;
    }
    queue.insert(u);
}

std::vector<Cell> DStar::computePath() {
    while (!queue.empty() && 
           (queue.top().key < calculateKey(start_) || start_.rhs != start_.g)) {

        Cell u = queue.pop();

        if (u.g > u.rhs) {
            u.g = u.rhs;
            for (auto &nbr : neighbors(u))
                updateVertex(nbr);
        } else {
            u.g = INF;
            updateVertex(u);
            for (auto &nbr : neighbors(u))
                updateVertex(nbr);
        }
    }

    return extractPath();
}
