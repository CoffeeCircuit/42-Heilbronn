# !/usr/bin/env python3
"""
loading
Directory: ex01/
Files to Submit: loading.py, requirements.txt, pyproject.toml
Authorized: pandas, requests, matplotlib, numpy, sys, importlib
"""

try:
    import pandas as pd  # type: ignore
    import numpy as np  # type: ignore
    import matplotlib.pyplot as plt  # type: ignore
except ImportError as e:
    print(f"Missing module: {e.name}. Please install all dependencies.")
    exit(1)

from importlib.metadata import version


def mandelbrot(
    xmin=-2.0,
    xmax=1.0,
    ymin=-1.5,
    ymax=1.5,
    width=800,
    height=800,
    max_iter=100,
):
    # Create complex plane
    x = np.linspace(xmin, xmax, width)
    y = np.linspace(ymin, ymax, height)
    X, Y = np.meshgrid(x, y)
    C = X + 1j * Y

    Z = np.zeros_like(C)
    escape = np.zeros(C.shape, dtype=int)

    mask = np.ones(C.shape, dtype=bool)

    for i in range(max_iter):
        Z[mask] = Z[mask] ** 2 + C[mask]
        mask = np.abs(Z) <= 2
        escape[mask] = i
    return escape


def loading() -> None:
    print("\nLOADING STATUS: Loading programs...")
    print("\nChecking dependencies:")

    print(f"[OK] pandas ({version('pandas')}) - Data manipulation ready")
    print(f"[OK] requests ({version('requests')}) - Network access ready")
    print(f"[OK] matplotlib ({version('matplotlib')}) - Visualization ready")
    print(f"[OK] numpy ({version('numpy')}) - Numerical computations ready")

    print("\nAnalyzing Matrix data...")
    print("Processing 100 data points...")
    escape = mandelbrot()
    df = pd.DataFrame(escape)

    print("Generating visualization...")
    plt.imshow(df, cmap="turbo")
    plt.colorbar(label="Iterations")
    plt.title("Mandelbrot Set")
    plt.savefig("matrix_analysis.png")
    plt.show()

    print("\nAnalysis complete!")
    print("Results saved to: matrix_analysis.png")


if __name__ == "__main__":
    loading()
