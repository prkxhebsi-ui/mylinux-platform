import tkinter as tk
from tkinter import ttk
from datetime import datetime
from host.apps import open_app, root_explorer


class Home:
    def __init__(self, root):
        self.root = root
        root.configure(bg="#101522")

        top = tk.Frame(root, bg="#202b40", height=42)
        top.pack(fill="x")

        tk.Label(
            top, text="  MyLinux",
            bg="#202b40", fg="#70cfff",
            font=("TkDefaultFont", 14, "bold")
        ).pack(side="left", padx=10)

        self.clock = tk.Label(
            top, bg="#202b40", fg="white"
        )
        self.clock.pack(side="right", padx=15)
        self.update_clock()

        center = tk.Frame(root, bg="#101522")
        center.pack(fill="both", expand=True, padx=25, pady=20)

        tk.Label(
            center,
            text="Welcome to MyLinux",
            bg="#101522", fg="white",
            font=("TkDefaultFont", 25, "bold")
        ).pack(anchor="w", pady=15)

        tk.Label(
            center,
            text="Homemade Cuttlefish • ARM64 • Native Termux mode",
            bg="#101522", fg="#9aaac2"
        ).pack(anchor="w", pady=4)

        grid = tk.Frame(center, bg="#101522")
        grid.pack(fill="both", expand=True, pady=25)

        apps = [
            ("☎", "Phone"),
            ("✉", "Message"),
            ("⚙", "Settings"),
            ("⌨", "Terminal"),
            ("◎", "Browser"),
            ("▣", "MyFiles"),
            ("▤", "System"),
        ]

        for i, (symbol, name) in enumerate(apps):
            card = tk.Frame(
                grid, bg="#202b40",
                highlightthickness=1,
                highlightbackground="#354764"
            )
            card.grid(
                row=i // 4, column=i % 4,
                padx=8, pady=8, sticky="nsew"
            )

            tk.Button(
                card,
                text=f"{symbol}\n\n{name}",
                command=lambda n=name: open_app(root, n),
                bg="#202b40", fg="white",
                activebackground="#314867",
                activeforeground="white",
                relief="flat",
                font=("TkDefaultFont", 13),
                width=15, height=5
            ).pack(fill="both", expand=True)

        for column in range(4):
            grid.columnconfigure(column, weight=1)
        for row in range(2):
            grid.rowconfigure(row, weight=1)

        dock = tk.Frame(root, bg="#202b40", height=55)
        dock.pack(side="bottom", fill="x")

        tk.Label(
            dock,
            text="MyLinux Desktop  |  Native Mode  |  No QEMU",
            bg="#202b40", fg="#a9bad3"
        ).pack(side="left", padx=15, pady=15)

        tk.Button(
            dock,
            text="Home",
            command=lambda: None
        ).pack(side="right", padx=12, pady=8)

        # Hidden Root Explorer: Ctrl+Alt+R
        root.bind_all(
            "<Control-Alt-r>",
            lambda event: root_explorer(root)
        )

        root.bind_all(
            "<Control-Alt-R>",
            lambda event: root_explorer(root)
        )

    def update_clock(self):
        self.clock.configure(
            text=datetime.now().strftime("%Y-%m-%d  %H:%M:%S")
        )
        self.root.after(1000, self.update_clock)
