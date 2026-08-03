import torch
import torch.nn as nn

class LatentDynamicsGRU(nn.Module):
    def __init__(self, latent_dim=256):
        super().__init__()
        self.gru = nn.GRU(latent_dim, latent_dim, batch_first=True)

    def forward(self, z_t):
        z_t = z_t.unsqueeze(1)
        out, _ = self.gru(z_t)
        return out.squeeze(1)
