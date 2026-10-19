import os
import csv
import argparse
import torch
import torch.nn as nn
from torch.utils.data import DataLoader
from dataset_builder import DroNetDataset
from train_dronet import DroNet

def evaluate(model_path, data_root, img_size=200, batch_size=64):
    ds = DroNetDataset(data_root, img_size=img_size)
    dl = DataLoader(ds, batch_size=batch_size, shuffle=False)

    model = DroNet().cuda()
    model.load_state_dict(torch.load(model_path))
    model.eval()

    mse_steer = 0.0
    mse_coll = 0.0
    n = 0

    with torch.no_grad():
        for img, y in dl:
            img, y = img.cuda(), y.cuda()
            pred = model(img)
            mse_steer += ((pred[:, 0] - y[:, 0]) ** 2).sum().item()
            mse_coll += ((pred[:, 1] - y[:, 1]) ** 2).sum().item()
            n += img.size(0)

    mse_steer /= n
    mse_coll /= n

    print(f"Steering MSE: {mse_steer:.4f}")
    print(f"Collision MSE: {mse_coll:.4f}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--model", required=True)
    parser.add_argument("--data", required=True)
    args = parser.parse_args()

    evaluate(args.model, args.data)
