#pragma once
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

class LocalMapper {
public:
    LocalMapper(double grid_size, double resolution);

    void update(const sensor_msgs::msg::PointCloud2 &pc);
    nav_msgs::msg::OccupancyGrid getGrid();

private:
    double grid_size_;
    double resolution_;
    int dim_;

    std::vector<int8_t> grid_;
};
