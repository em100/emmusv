import torch
import torch.nn as nn

class LatentDynamicsTransformer(nn.Module):
    def __init__(self, latent_dim=256, num_layers=4, num_heads=8):
        super().__init__()
        layer = nn.TransformerEncoderLayer(
            d_model=latent_dim,
            nhead=num_heads
        )
        self.encoder = nn.TransformerEncoder(layer, num_layers=num_layers)

    def forward(self, z_t):
        z_t = z_t.unsqueeze(1)
        out = self.encoder(z_t)
        return out.squeeze(1)
