import tkinter as tk


class GraphCanvas(tk.Canvas):
    def __init__(self, master, **kwargs):
        super().__init__(master, **kwargs)
        self.scale_factor = 1.0
        self._drag_data = {"x": 0, "y": 0}
        self.text_items = {}  # item_id: (base_font_name, base_font_size, ...)
        self.bind("<ButtonPress-1>", self.start_pan)
        self.bind("<B1-Motion>", self.do_pan)
        self.bind("<MouseWheel>", self.do_zoom)  # Windows/macOS
        self.bind("<Button-4>", self.do_zoom)  # Linux scroll up
        self.bind("<Button-5>", self.do_zoom)  # Linux scroll down

    def create_text_scaled(self, *args, font=None, **kwargs):
        # font: tuple (font_name, base_size, *options)
        item = self.create_text(*args, font=font, **kwargs)
        if font is not None:
            # Store base font info for scaling
            self.text_items[item] = (
                font[0],
                font[1],
                font[2:] if len(font) > 2 else (),
            )
        return item

    def start_pan(self, event):
        self._drag_data["x"] = event.x
        self._drag_data["y"] = event.y

    def do_pan(self, event):
        dx = event.x - self._drag_data["x"]
        dy = event.y - self._drag_data["y"]
        self.move("all", dx, dy)
        self._drag_data["x"] = event.x
        self._drag_data["y"] = event.y

    def do_zoom(self, event):
        # Cross-platform zoom direction
        factor = None
        if hasattr(event, "delta") and event.delta != 0:
            factor = 1.1 if event.delta > 0 else 0.9
        elif hasattr(event, "num"):
            if event.num == 4:
                factor = 1.1
            elif event.num == 5:
                factor = 0.9
        if factor is None:
            return
        # Clamp scale factor to avoid disappearing
        new_scale = self.scale_factor * factor
        if 0.2 < new_scale < 5:
            self.scale("all", event.x, event.y, factor, factor)
            self.scale_factor = new_scale
            self._rescale_texts()

    def _rescale_texts(self):
        for item, (font_name, base_size, font_opts) in self.text_items.items():
            new_size = max(1, int(base_size * self.scale_factor))
            new_font = (font_name, new_size) + tuple(font_opts)
            self.itemconfig(item, font=new_font)


def animate_node(canvas, node_id, dx, dy, steps=50, delay=10):
    def step(count):
        if count < steps:
            canvas.move(node_id, dx / steps, dy / steps)
            canvas.after(delay, step, count + 1)

    step(0)


root = tk.Tk()
root.title("Fly-In")
canvas = GraphCanvas(
    root, bd=0, highlightthickness=0, bg="#1e1e2e", width=800, height=800
)
canvas.pack(fill="both", expand=True)

# Example: Draw a node and animate it
node = canvas.create_oval(
    100, 100, 140, 140, fill="#1e1e2e", outline="#94e2d5", width=3
)
canvas.create_text_scaled(
    120, 120, text="A", fill="#fab387", font=("Arial", 16, "bold")
)
animate_node(canvas, node, 200, 0, steps=100, delay=5)

tip = tk.Toplevel()


root.mainloop()
