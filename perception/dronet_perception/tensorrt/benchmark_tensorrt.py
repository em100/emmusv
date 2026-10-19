import time
import argparse
import numpy as np
import cv2
import tensorrt as trt
import pycuda.driver as cuda
import pycuda.autoinit

def load_engine(engine_path):
    logger = trt.Logger(trt.Logger.INFO)
    with open(engine_path, "rb") as f:
        runtime = trt.Runtime(logger)
        engine = runtime.deserialize_cuda_engine(f.read())
    context = engine.create_execution_context()
    return engine, context

def benchmark(engine_path, img_size=200, runs=500):
    engine, context = load_engine(engine_path)
    input_idx = engine.get_binding_index("input")
    output_idx = engine.get_binding_index("output")

    input_shape = (1, 3, img_size, img_size)
    output_shape = (1, 2)

    d_input = cuda.mem_alloc(np.prod(input_shape) * np.float32().nbytes)
    d_output = cuda.mem_alloc(np.prod(output_shape) * np.float32().nbytes)

    bindings = [None] * engine.num_bindings
    bindings[input_idx] = int(d_input)
    bindings[output_idx] = int(d_output)

    img = np.random.rand(*input_shape).astype(np.float32)

    cuda.memcpy_htod(d_input, img)

    # warmup
    for _ in range(50):
        context.execute_v2(bindings)

    times = []
    for _ in range(runs):
        t0 = time.time()
        context.execute_v2(bindings)
        t1 = time.time()
        times.append((t1 - t0) * 1000.0)

    print(f"Engine: {engine_path}")
    print(f"Mean latency: {np.mean(times):.3f} ms")
    print(f"Std latency: {np.std(times):.3f} ms")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--engine", required=True)
    parser.add_argument("--runs", type=int, default=500)
    args = parser.parse_args()

    benchmark(args.engine, runs=args.runs)
