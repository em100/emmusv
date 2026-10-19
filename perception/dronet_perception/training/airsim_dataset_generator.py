import os
import csv
import argparse
from pathlib import Path
import airsim
import cv2

def record_episode(client, out_dir, episode_id, num_steps=1000):
    episode_dir = Path(out_dir) / f"episode_{episode_id}"
    img_dir = episode_dir / "images"
    img_dir.mkdir(parents=True, exist_ok=True)

    csv_path = episode_dir / "labels.csv"
    csv_file = open(csv_path, "w", newline="")
    writer = csv.DictWriter(csv_file, fieldnames=["filename", "steering", "collision"])
    writer.writeheader()

    for step in range(num_steps):
        # simple random steering policy
        steering = client.getCarControls().steering
        collision = int(client.simGetCollisionInfo().has_collided)

        resp = client.simGetImages([
            airsim.ImageRequest("0", airsim.ImageType.Scene, False, False)
        ])[0]
        img = airsim.to_numpy(resp)
        img_name = f"frame_{step:06d}.png"
        cv2.imwrite(str(img_dir / img_name), img)

        writer.writerow({
            "filename": img_name,
            "steering": steering,
            "collision": collision
        })

    csv_file.close()

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--out", required=True)
    parser.add_argument("--episodes", type=int, default=10)
    parser.add_argument("--steps", type=int, default=1000)
    args = parser.parse_args()

    client = airsim.CarClient()
    client.confirmConnection()
    client.enableApiControl(True)

    for ep in range(args.episodes):
        client.reset()
        record_episode(client, args.out, ep, num_steps=args.steps)

if __name__ == "__main__":
    main()
