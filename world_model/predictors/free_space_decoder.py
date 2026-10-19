import torch
import torch.nn as nn

class FreeSpaceDecoder(nn.Module):
    def __init__(self, latent_dim=256):
        super().__init__()
        self.fc = nn.Sequential(
            nn.Linear(latent_dim, 512),
            nn.ReLU(),
            nn.Linear(512, 128*128)
        )

    def forward(self, z):
        return self.fc(z).reshape(-1, 1, 128, 128)
