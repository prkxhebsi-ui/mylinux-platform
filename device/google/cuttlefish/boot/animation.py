import tkinter as tk
from tkinter import ttk


def start_boot(root, callback):
    for widget in root.winfo_children():
        widget.destroy()

    root.configure(bg="#101522")
    root.title("MyLinux Boot")

    canvas = tk.Canvas(
        root,
        bg="#101522",
        highlightthickness=0
    )
    canvas.pack(fill="both", expand=True)

    canvas.create_text(
        500, 220,
        text="MyLinux",
        fill="#66ccff",
        font=("TkDefaultFont", 42, "bold")
    )

    canvas.create_text(
        500, 275,
        text="HOMEMADE CUTTLEFISH",
        fill="#aaaaaa",
        font=("TkDefaultFont", 13)
    )

    bar = ttk.Progressbar(
        root,
        mode="determinate",
        maximum=100,
        length=420
    )

    canvas.create_window(
        500, 360,
        window=bar
    )

    status = canvas.create_text(
        500, 405,
        text="Initializing...",
        fill="white",
        font=("TkDefaultFont", 11)
    )

    steps = [
        "Loading device configuration...",
        "Initializing SQLite database...",
        "Starting desktop services...",
        "Loading application registry...",
        "Preparing virtual filesystem...",
        "Starting MyLinux desktop...",
        "Welcome to MyLinux!"
    ]

    def advance(index=0):
        if index >= len(steps):
            root.after(500, callback)
            return

        bar["value"] = int(
            (index + 1) / len(steps) * 100
        )

        canvas.itemconfigure(
            status,
            text=steps[index]
        )

        root.after(
            450,
            lambda: advance(index + 1)
        )

    advance()
