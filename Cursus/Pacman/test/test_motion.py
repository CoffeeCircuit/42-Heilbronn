import pygame
import sys

pygame.init()

screen = pygame.display.set_mode(
    (800, 600),
    vsync=1
)

clock = pygame.time.Clock()

surf = pygame.Surface((70, 80))
surf.fill((50, 120, 255))

x = 0.0
speed = 180.0

while True:
    dt = clock.tick() / 1000.0

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    x += speed * dt

    screen.fill((0, 0, 0))

    screen.blit(surf, (x, 300))

    pygame.display.flip()
