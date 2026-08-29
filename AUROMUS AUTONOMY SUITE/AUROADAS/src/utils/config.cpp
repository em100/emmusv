#include "rclcpp/rclcpp.hpp"
#include "yaml-cpp/yaml.h"
#include <string>
#include <unordered_map>

namespace auroadas {

class Config {
public:
    Config(rclcpp::Logger logger)
        : logger_(logger)
    {}

    bool load(const std::string& path) {
        try {
            data_ = YAML::LoadFile(path);
            RCLCPP_INFO(logger_, "Loaded config: %s", path.c_str());
            return true;
        } catch (const std::exception& e) {
            RCLCPP_ERROR(logger_, "Failed to load config %s: %s",
                         path.c_str(), e.what());
            return false;
        }
    }

    template<typename T>
    T get(const std::string& key, const T& default_value) const {
        if (!data_[key]) {
            return default_value;
        }
        return data_[key].as<T>();
    }

private:
    rclcpp::Logger logger_;
    YAML::Node data_;
};

} // namespace auroadas
