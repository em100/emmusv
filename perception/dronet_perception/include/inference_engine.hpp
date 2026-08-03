#pragma once
#include <opencv2/opencv.hpp>
#include <NvInfer.h>

class InferenceEngine {
public:
    InferenceEngine(const std::string &engine_path);
    ~InferenceEngine();

    std::pair<float, float> infer(const cv::Mat &img);

private:
    nvinfer1::IRuntime *runtime_;
    nvinfer1::ICudaEngine *engine_;
    nvinfer1::IExecutionContext *context_;

    void *buffers_[2];
    int input_idx_, output_idx_;
};
