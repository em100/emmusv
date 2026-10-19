#include "inference_engine.hpp"
#include <cuda_runtime_api.h>
#include <fstream>

InferenceEngine::InferenceEngine(const std::string &engine_path) {
    std::ifstream file(engine_path, std::ios::binary);
    std::vector<char> data((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());

    runtime_ = nvinfer1::createInferRuntime(gLogger);
    engine_ = runtime_->deserializeCudaEngine(data.data(), data.size());
    context_ = engine_->createExecutionContext();

    input_idx_ = engine_->getBindingIndex("input");
    output_idx_ = engine_->getBindingIndex("output");

    cudaMalloc(&buffers_[input_idx_], 3 * 200 * 200 * sizeof(float));
    cudaMalloc(&buffers_[output_idx_], 2 * sizeof(float));
}

InferenceEngine::~InferenceEngine() {
    cudaFree(buffers_[input_idx_]);
    cudaFree(buffers_[output_idx_]);
    context_->destroy();
    engine_->destroy();
    runtime_->destroy();
}

std::pair<float, float> InferenceEngine::infer(const cv::Mat &img) {
    cv::Mat resized;
    cv::resize(img, resized, cv::Size(200, 200));
    resized.convertTo(resized, CV_32F, 1.0 / 255.0);

    cudaMemcpy(buffers_[input_idx_], resized.data,
               3 * 200 * 200 * sizeof(float), cudaMemcpyHostToDevice);

    context_->executeV2(buffers_);

    float output[2];
    cudaMemcpy(output, buffers_[output_idx_], 2 * sizeof(float),
               cudaMemcpyDeviceToHost);

    return {output[0], output[1]};
}
