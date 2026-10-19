
import os
import cv2
import argparse

def build_calibration_dataset(src_root, dst_root, img_size=200, max_images=500):
    os.makedirs(dst_root, exist_ok=True)
    count = 0

    for root, _, files in os.walk(src_root):
        for f in files:
            if not f.endswith(".png") and not f.endswith(".jpg"):
                continue

            img = cv2.imread(os.path.join(root, f))
            img = cv2.resize(img, (img_size, img_size))
            cv2.imwrite(os.path.join(dst_root, f), img)

            count += 1
            if count >= max_images:
                return

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--src", required=True)
    parser.add_argument("--dst", required=True)
    parser.add_argument("--max", type=int, default=500)
    args = parser.parse_args()

    build_calibration_dataset(args.src, args.dst, max_images=args.max)
