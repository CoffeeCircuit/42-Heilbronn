import pygame
import os

BASETILEWIDTH = 16
BASETILEHEIGHT = 16


class Spritesheet(object):
    def __init__(self):
        sprite_path = os.path.join(
            os.path.dirname(__file__), "../../assets/sprites/pacman.png"
        )
        self.sheet = pygame.image.load(sprite_path).convert()

    def getImage(self, x, y):
        self.sheet.set_clip(pygame.Rect(x, y, 32, 32))
        # Copy the subsurface instead of returning a view
        return self.sheet.subsurface(self.sheet.get_clip()).copy()
