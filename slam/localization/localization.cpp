#include <Eigen/Dense>

class Localization
{
public:

    void update(
        const Eigen::Vector3d& position,
        const Eigen::Quaterniond& orientation)
    {
        position_ = position;
        orientation_ = orientation;
    }

private:

    Eigen::Vector3d position_;

    Eigen::Quaterniond orientation_;
};