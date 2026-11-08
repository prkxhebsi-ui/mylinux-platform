import tkinter as tk
from pathlib import Path
import sys
import logging

BASE = Path(__file__).resolve().parents[1]
PROJECT = BASE.parents[2]

sys.path.insert(0, str(BASE))

from boot.animation import start_boot
from desktop.home import Home


def main():
    root = tk.Tk()
    root.title("MyLinux Homemade Cuttlefish")
    root.geometry("1000x700")
    root.minsize(700, 500)

    def show_home():
        for widget in root.winfo_children():
            widget.destroy()
        Home(root)

    logging.info("MyLinux desktop starting")
    start_boot(root, show_home)
    root.mainloop()


if __name__ == "__main__":
    main()
