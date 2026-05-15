from .config import Config
from .sprites import Spritesheet

import pygame
import time


def pacman(cfg_file_path):
    cfg = Config()

    if not cfg.read(cfg_file_path):
        exit()

    pygame.init()
    window = pygame.display.set_mode((cfg.width, cfg.height), vsync=1)
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

    print(f"Display: {cfg.width}x{cfg.height}")
    print(f"VSync: Enabled")
    print(f"Target FPS: {fps}")

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

            # Print timing stats every 60 frames
            if frame_counter % 60 == 0 and frame_times:
                avg_dt = sum(frame_times) / len(frame_times)
                min_dt = min(frame_times)
                max_dt = max(frame_times)
                print(
                    f"Timing - Avg: {avg_dt * 1000:.2f}ms, Min: {min_dt * 1000:.2f}ms, Max: {max_dt * 1000:.2f}ms"
                )
                frame_times = []

            window.fill((0, 0, 0))
            window.blit(frames[frame_index], (x, 100))
            pygame.display.flip()

    pygame.quit()
