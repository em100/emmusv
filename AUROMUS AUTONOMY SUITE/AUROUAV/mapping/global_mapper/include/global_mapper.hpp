#pragma once
#include <vector>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>

class GlobalMapper {
public:
    GlobalMapper(double map_size, double voxel_res);

    void update(const sensor_msgs::msg::PointCloud2 &pc);
    void updateSemantic(const cv::Mat &mask);

    std::vector<uint8_t> getVoxelMap();

private:
    double map_size_;
    double voxel_res_;
    int dim_;

    std::vector<uint8_t> voxels_;
    std::vector<uint8_t> semantic_;
};
