import tkinter as tk

from config import Configure
from math import sin, cos

root = tk.Tk()
root.geometry(f"{Configure.width}x{Configure.height}")
root.configure(bg=Configure.background)

root.bind("<q>", lambda e: root.destroy())

frame = tk.Frame(root)

canvas = tk.Canvas(
    root,
    bg=Configure.background,
    highlightthickness=0,
)

slider_delay = tk.Scale(
    frame,
    bg=Configure.background,
    fg=Configure.foreground,
    highlightthickness=0,
    label="Delay (ms)",
    from_=0,
    to=100,
    resolution=5,
    length=200,
    tickinterval=20,
    showvalue=False,
    orient=tk.HORIZONTAL,
)

slider_steps = tk.Scale(
    frame,
    bg=Configure.background,
    fg=Configure.foreground,
    highlightthickness=0,
    label="Steps per turn",
    from_=0,
    to=100,
    resolution=5,
    length=200,
    tickinterval=20,
    showvalue=False,
    orient=tk.HORIZONTAL,
)


slider_delay.set(Configure.animation_delay)
slider_steps.set(Configure.animation_steps)


frame.pack(anchor="ne")
slider_delay.pack(side=tk.LEFT)
slider_steps.pack(side=tk.LEFT)
canvas.pack(side=tk.BOTTOM, expand=True, fill="both")


def create_drone(x_c: int, y_c: int):
    half_size = Configure.drone_size * 0.5
    return canvas.create_oval(
        x_c - half_size,
        y_c - half_size,
        x_c + half_size,
        y_c + half_size,
        fill=Configure.drone_color,
    )


def create_cluster(x_c, y_c, n):

    start_angle = 0
    R = 2 * Configure.drone_size

    def draw_ring(R, start_angle, n):
        spacing = 360 / n
        for j in range(n):
            angle = (j * spacing + start_angle) * 0.017453293
            x_i = R * cos(angle) + x_c
            y_i = R * sin(angle) + y_c
            create_drone(x_i, y_i)

    chunk = 10
    total = 0
    while total + chunk <= n:
        draw_ring(R, start_angle, chunk)
        total += chunk
        chunk += 10
        R += 2 * Configure.drone_size
    if n - total > 0:
        draw_ring(R, start_angle, n - total)


test_graph = [(0, 0), (1, 0), (2, 0), (3, 0), (4, 0), (5, 0), (1, 1), (2, 1), (3, 1), (4, 1), (1, -1), (2, -1), (3, -1), (4, -1), (1, 2), (2, 2), (3, 2), (4, 2), (5, 2), (5, 1), (6, 0), (7, 0), (8, 0), (6, 1), (7, 1), (8, 1), (6, -1), (7, -1), (8, -1), (9, 0), (10, 0), (11, 0), (9, 1), (10, 1), (11, 1), (9, -1), (10, -1), (11, -1), (12, 2), (13, 2), (14, 2), (12, 0), (13, 0), (14, 0), (12, -2), (13, -2), (14, -2), (15, 0), (16, 0), (17, 0), (18, 0), (19, 0), (20, 0), (21, 0)]


def center(nodes: list[tuple[int, int]]) -> list[tuple[float, float]]:
    if not nodes:
        return []

    # Initialize to first node
    x0_bbox = x1_bbox = nodes[0][0]
    y0_bbox = y1_bbox = nodes[0][1]

    for x, y in nodes:
        x0_bbox = min(x0_bbox, x)
        y0_bbox = min(y0_bbox, y)
        x1_bbox = max(x1_bbox, x)
        y1_bbox = max(y1_bbox, y)

    # Handle single point or line cases
    width_bbox = x1_bbox - x0_bbox
    height_bbox = y1_bbox - y0_bbox

    if width_bbox == 0 and height_bbox == 0:
        scale = 1
    elif width_bbox == 0:
        scale = Configure.height / height_bbox * 0.9
    elif height_bbox == 0:
        scale = Configure.width / width_bbox * 0.9
    else:
        scale = min(Configure.width / width_bbox,
                    Configure.height / height_bbox) * 0.9

    # Center of nodes
    x_c = (x0_bbox + x1_bbox) / 2
    y_c = (y0_bbox + y1_bbox) / 2

    # Scale, center, and translate to canvas center
    return [
        ((x - x_c) * scale + Configure.width / 2,
         (y - y_c) * scale + Configure.height / 2)
        for x, y in nodes
    ]


for node in center(test_graph):
    create_drone(*node)


root.mainloop()
