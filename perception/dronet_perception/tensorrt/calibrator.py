import tensorrt as trt
import numpy as np
import os
import cv2

class ImageCalibrator(trt.IInt8EntropyCalibrator2):
    def __init__(self, image_dir, batch_size=8):
        super().__init__()
        self.image_paths = [os.path.join(image_dir, f) for f in os.listdir(image_dir)]
        self.batch_size = batch_size
        self.current = 0
        self.device_input = None

    def get_batch_size(self):
        return self.batch_size

    def get_batch(self, names):
        if self.current + self.batch_size >= len(self.image_paths):
            return None

        batch = []
        for i in range(self.batch_size):
            img = cv2.imread(self.image_paths[self.current + i])
            img = cv2.resize(img, (200, 200))
            img = img.astype(np.float32) / 255.0
            batch.append(img)

        batch = np.ascontiguousarray(np.array(batch))
        if self.device_input is None:
            self.device_input = cuda.mem_alloc(batch.nbytes)

        cuda.memcpy_htod(self.device_input, batch)
        self.current += self.batch_size
        return [int(self.device_input)]

    def read_calibration_cache(self):
        return None

    def write_calibration_cache(self, cache):
        pass
