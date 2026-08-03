import tensorrt as trt
import argparse

def build_engine(onnx_path, engine_path, fp16=False, int8=False):
    logger = trt.Logger(trt.Logger.INFO)
    builder = trt.Builder(logger)
    network = builder.create_network(1 << int(trt.NetworkDefinitionCreationFlag.EXPLICIT_BATCH))
    parser = trt.OnnxParser(network, logger)

    with open(onnx_path, "rb") as f:
        parser.parse(f.read())

    config = builder.create_builder_config()
    config.max_workspace_size = 1 << 30

    if fp16:
        config.set_flag(trt.BuilderFlag.FP16)
    if int8:
        config.set_flag(trt.BuilderFlag.INT8)

    engine = builder.build_engine(network, config)

    with open(engine_path, "wb") as f:
        f.write(engine.serialize())

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--onnx", required=True)
    parser.add_argument("--engine", required=True)
    parser.add_argument("--fp16", action="store_true")
    parser.add_argument("--int8", action="store_true")
    args = parser.parse_args()

    build_engine(args.onnx, args.engine, args.fp16, args.int8)
