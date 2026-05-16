from .config import Config
from .sprites import Spritesheet
from .font import Text
from .maze import Maze

import pygame
import time


def pacman(cfg_file_path):
    cfg = Config()

    if not cfg.read(cfg_file_path):
        exit()

    pygame.init()
    # Calculate window size based on maze dimensions (each cell is 32x32 pixels)
    # Maze grid is (width*2+1) x (height*2+1) cells after rendering
    TILE_SIZE = 32
    window_width = (cfg.width * 2 + 1) * TILE_SIZE
    window_height = (cfg.height * 2 + 1) * TILE_SIZE
    window = pygame.display.set_mode((window_width, window_height), vsync=1)
    pygame.display.set_caption("Pac-Man")
    window.fill((0, 0, 0))
    pygame.display.update()
    
    maze = Maze(window, cfg)

    running = True

    animation_frame_duration = 1.0 / 15.0  # 15 FPS for smoother animation
    num_frames = 3
    speed = 200  # pixels per second
    fps = 60
    pixels_per_frame = int(speed / fps)

    # Pre-load all animation frames once
    spritesheet = Spritesheet()
    frames = [spritesheet.getImage(0, i * 32) for i in range(num_frames)]

    frame_cap = 1.0 / fps
    frame_counter = 0
    animation_elapsed = 0.0

    time_1 = time.perf_counter()
    unprocessed = 0.0
    frame_times = []

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Accumulate time
        can_render = False
        time_2 = time.perf_counter()
        passed = time_2 - time_1
        unprocessed += passed
        time_1 = time_2

        # Update at fixed timestep
        while unprocessed >= frame_cap:
            unprocessed -= frame_cap
            frame_counter += 1
            animation_elapsed += frame_cap
            can_render = True

        # Render
        if can_render:
            x = frame_counter * pixels_per_frame
            frame_index = int(
                (animation_elapsed / animation_frame_duration) % num_frames
            )
            frame_times.append(passed)

            window.fill((0, 0, 0))
            maze.draw()
            window.blit(frames[frame_index], (x, 100))

            font = Text()
            font_surf = font.render("0123456")
            window.blit(font_surf, (0, 0))


            pygame.display.flip()

    pygame.quit()
