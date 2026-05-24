import pygame
import os


class Spritesheet(object):
    def __init__(self, filename: str = "pacman.png"):

        sprite_path = os.path.join(
            os.path.dirname(os.path.abspath(__file__)),
            f"../../assets/sprites/{filename}",
        )
        self.sheet = pygame.image.load(sprite_path).convert()

    def getImage(self, x: int, y: int) -> pygame.SurfaceType:
        self.sheet.set_clip(pygame.Rect(x, y, 32, 32))
        # Copy the subsurface instead of returning a view
        return self.sheet.subsurface(self.sheet.get_clip()).copy()
