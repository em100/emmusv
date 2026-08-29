import torch
import torch.nn as nn
from einops import rearrange

class PatchEmbed(nn.Module):
    def __init__(self, patch_size=16, embed_dim=256):
        super().__init__()
        self.proj = nn.Conv2d(3, embed_dim, patch_size, patch_size)

    def forward(self, x):
        x = self.proj(x)
        return rearrange(x, 'b c h w -> b (h w) c')

class ViTEncoder(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.patch = PatchEmbed(
            patch_size=config["patch_size"],
            embed_dim=config["embed_dim"]
        )
        encoder_layer = nn.TransformerEncoderLayer(
            d_model=config["embed_dim"],
            nhead=config["num_heads"]
        )
        self.transformer = nn.TransformerEncoder(
            encoder_layer,
            num_layers=config["num_layers"]
        )

    def forward(self, x):
        x = self.patch(x)
        x = self.transformer(x)
        return x.mean(dim=1)
