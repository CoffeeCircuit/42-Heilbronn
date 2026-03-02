import logging
from argparse import ArgumentParser
from pathlib import Path
from parser import Parser
from graph import Graph
from simulation import Simulator
from visualizer import GraphCanvas
import tkinter as tk
from scheduler import PathPlanner, Scheduler


def main():
    logging.basicConfig(
        level=logging.INFO, format="%(levelname)s:%(name)s: %(message)s"
    )

    arg_par = ArgumentParser(
        description="Drone routing simulator"
    )
    arg_par.add_argument("path", help="Path to map file")
    arg_par.add_argument(
        "-v",
        "--visual",
        action="store_true",
        help="Enable visual mode: colored terminal output and GUI graph",
    )
    arg_par.add_argument("-d", "--debug", action="store_true")
    args = arg_par.parse_args()

    logger = logging.getLogger("fly-in")
    logger.setLevel(logging.INFO)
    if args.debug:
        logger.setLevel(logging.DEBUG)

    file_path = Path(args.path)
    logger.debug(f"{file_path=}")

    visual_output = False
    if args.visual:
        visual_output = True

    logger.debug(f"{visual_output=}")

    if not file_path.exists():
        print("The target directory doesn't exist")
        raise SystemExit(1)

    # Parse map file
    file_parser = Parser()
    try:
        file_parser.parse(args.path)
        logger.debug(f"Parsed {len(file_parser.tokens)} tokens")
    except Exception as e:
        logger.error(f"Parsing failed: {e}")
        raise SystemExit(1)

    # Build graph from tokens
    graph = Graph()
    try:
        graph.build_from_tokens(file_parser.tokens)
        logger.debug(f"Built graph: {graph}")
    except Exception as e:
        logger.error(f"Graph construction failed: {e}")
        raise SystemExit(1)

    # Verify start and end exist
    if not graph.start or not graph.end:
        logger.error("Map must have exactly one start_hub and one end_hub")
        raise SystemExit(1)

    # Plan paths for all drones
    try:
        planner = PathPlanner(graph, file_parser.nb_drones)
        assignments = planner.assign_drones()

    except Exception as e:
        logger.error(f"Path planning failed: {e}")
        import traceback

        traceback.print_exc()
        raise SystemExit(1)

    # Initialize simulator
    simulator = Simulator(graph, file_parser.nb_drones)

    # Assign paths to drones in simulator
    for drone_id, path in assignments.items():
        if drone_id <= len(simulator.drones):
            simulator.drones[drone_id - 1].path = path

    # Run simulation
    try:
        scheduler = Scheduler(simulator, assignments, visual=visual_output)
        output = scheduler.schedule_and_run()

        # Output results to stdout
        if not visual_output:
            print(output)
        logger.debug(f"Simulation completed in {simulator.turn} turns")

        # Performance feedback
        turns = simulator.turn
        if "easy" in str(file_path) and turns <= 10:
            logger.debug("Performance: Excellent")
        elif "medium" in str(file_path) and turns <= 30:
            logger.debug("Performance: Good (Medium map within target)")
        elif "hard" in str(file_path) and turns <= 60:
            logger.debug("Performance: Acceptable (Hard map within target)")
        else:
            logger.warning(f"Performance: {turns} turns may need optimization")

    except Exception as e:
        print(e)

    # Visual output if requested - show GUI
    if visual_output:
        logger.info("Displaying graph visualization...")
        try:
            # Create Tkinter window
            root = tk.Tk()
            root.title(f"Drone Routing - {file_path.name}")
            root.geometry("1920x1080")

            # Create canvas
            canvas = GraphCanvas(root, bg="#1e1e1e", highlightthickness=0)
            canvas.pack(fill=tk.BOTH, expand=True)

            # Draw the graph
            canvas.create_graph(graph.adj_lst)

            # Initialize drones at start position
            for drone in simulator.drones:
                canvas.create_drone(drone.id, simulator.start_hub)

            # Set animation data
            movements = scheduler.get_movements_for_animation()
            canvas.set_animation_data(movements)

            # Add info label and controls
            control_frame = tk.Frame(root, bg="#2d2d2d")
            control_frame.pack(side=tk.BOTTOM, fill=tk.X)

            info_label = tk.Label(
                control_frame,
                text=f"Completed in {simulator.turn} turns | {simulator.nb_drones} drones | "
                f"Start: {simulator.start_hub.name} → End: {simulator.end_hub.name}",
                bg="#2d2d2d",
                fg="white",
                pady=10,
            )
            info_label.pack(side=tk.LEFT, padx=10)

            # Turn counter display
            turn_counter = tk.Label(
                control_frame,
                text="Turn: 0 / "
                + str(len(scheduler.get_movements_for_animation())),
                bg="#2d2d2d",
                fg="#4CAF50",
                font=("Arial", 12, "bold"),
                pady=10,
            )
            turn_counter.pack(side=tk.LEFT, padx=20)

            # Update turn counter function
            def update_turn_display():
                turn_counter.config(
                    text=f"Turn: {canvas.current_turn} / {len(canvas.animation_queue)}"
                )
                root.after(100, update_turn_display)

            update_turn_display()

            # Control buttons frame
            button_frame = tk.Frame(control_frame, bg="#2d2d2d")
            button_frame.pack(side=tk.RIGHT, padx=10)

            # Restart button
            restart_button = tk.Button(
                button_frame,
                text="⟲ Restart",
                command=canvas.restart_animation,
                bg="#FF9800",
                fg="white",
                padx=15,
                pady=5,
            )
            restart_button.pack(side=tk.LEFT, padx=2)

            # Previous turn button
            prev_button = tk.Button(
                button_frame,
                text="◀ Prev",
                command=canvas.previous_turn,
                bg="#2196F3",
                fg="white",
                padx=15,
                pady=5,
            )
            prev_button.pack(side=tk.LEFT, padx=2)

            # Pause button
            pause_button = tk.Button(
                button_frame,
                text="⏸ Pause",
                command=canvas.pause_animation,
                bg="#FFC107",
                fg="white",
                padx=15,
                pady=5,
            )
            pause_button.pack(side=tk.LEFT, padx=2)

            # Play animation button
            play_button = tk.Button(
                button_frame,
                text="▶ Play",
                command=canvas.play_animation,
                bg="#4CAF50",
                fg="white",
                padx=15,
                pady=5,
            )
            play_button.pack(side=tk.LEFT, padx=2)

            # Next turn button
            next_button = tk.Button(
                button_frame,
                text="Next ▶",
                command=canvas.next_turn,
                bg="#2196F3",
                fg="white",
                padx=15,
                pady=5,
            )
            next_button.pack(side=tk.LEFT, padx=2)

            logger.info(
                "GUI window opened. Use controls: "
                "Restart | Prev | Pause | Play | Next"
            )
            root.mainloop()
        except Exception as e:
            logger.error(f"Failed to create visualization: {e}")
            import traceback

            traceback.print_exc()


if __name__ == "__main__":
    main()
