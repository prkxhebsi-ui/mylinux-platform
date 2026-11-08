import tkinter as tk
from tkinter import ttk, messagebox, filedialog
from pathlib import Path
import subprocess
import sqlite3
import socket
import urllib.request
import threading
import json
import tomllib
import os
import sys
import datetime
import logging

BASE = Path(__file__).resolve().parents[1]
PROJECT = BASE.parents[2]
VROOT = PROJECT / "c"

DB = BASE / "database" / "devices.db"
LOG = BASE / "logs" / "desktop.log"

logging.basicConfig(
    filename=str(LOG),
    level=logging.INFO,
    format="%(asctime)s %(levelname)s %(message)s"
)

DB.parent.mkdir(parents=True, exist_ok=True)

def database():
    con = sqlite3.connect(DB)
    con.execute("""
        CREATE TABLE IF NOT EXISTS messages (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            sender TEXT,
            body TEXT,
            created_at TEXT
        )
    """)
    con.execute("""
        CREATE TABLE IF NOT EXISTS devices (
            id TEXT PRIMARY KEY,
            name TEXT,
            architecture TEXT,
            state TEXT,
            created_at TEXT
        )
    """)
    con.commit()
    return con


def window(parent, title, size="650x450"):
    win = tk.Toplevel(parent)
    win.title("MyLinux - " + title)
    win.geometry(size)
    win.configure(bg="#171d2b")
    return win


def label(parent, text):
    return tk.Label(
        parent, text=text,
        bg="#171d2b", fg="white",
        font=("TkDefaultFont", 11)
    )


def button(parent, text, command):
    return ttk.Button(parent, text=text, command=command)


# PHONE
def phone(parent):
    win = window(parent, "Phone", "500x430")

    label(win, "MyLinux Phone").pack(pady=15)

    number = tk.Entry(win, font=("TkDefaultFont", 17))
    number.pack(padx=20, fill="x")

    result = tk.Text(win, height=10, bg="#0e1420", fg="#8de0ff")
    result.pack(fill="both", expand=True, padx=15, pady=15)

    def network_check():
        try:
            host = socket.gethostname()
            address = socket.gethostbyname(host)
            result.insert("end", f"Hostname: {host}\nIP: {address}\n")
            result.insert("end", "Network socket support available.\n")
            result.insert("end", "VoIP calling is not configured yet.\n")
        except OSError as exc:
            result.insert("end", f"Network error: {exc}\n")

    button(win, "Check network", network_check).pack(pady=8)
    button(win, "Clear", lambda: result.delete("1.0", "end")).pack()


# MESSAGE
def message(parent):
    win = window(parent, "Message", "600x500")

    label(win, "MyLinux Messages").pack(pady=10)

    history = tk.Text(win, bg="#0e1420", fg="white")
    history.pack(fill="both", expand=True, padx=12, pady=8)

    sender = tk.Entry(win)
    sender.insert(0, "Local user")
    sender.pack(fill="x", padx=12)

    body = tk.Entry(win)
    body.pack(fill="x", padx=12, pady=8)

    def refresh():
        history.delete("1.0", "end")
        con = database()
        rows = con.execute(
            "SELECT sender, body, created_at FROM messages ORDER BY id"
        ).fetchall()
        con.close()

        for who, text, stamp in rows:
            history.insert("end", f"[{stamp}] {who}: {text}\n")

    def send():
        text = body.get().strip()
        if not text:
            return

        con = database()
        con.execute(
            "INSERT INTO messages(sender,body,created_at) VALUES(?,?,?)",
            (sender.get(), text, datetime.datetime.now().isoformat())
        )
        con.commit()
        con.close()
        body.delete(0, "end")
        refresh()

    button(win, "Save message", send).pack(pady=5)
    button(win, "Refresh", refresh).pack()
    refresh()


# SETTINGS
def settings(parent):
    win = window(parent, "Settings", "750x560")

    label(win, "Configuration editor").pack(pady=8)

    choices = {
        "Device TOML": BASE / "config" / "device.toml",
        "Applications JSON": BASE / "config" / "apps.json",
        "Settings JSON": BASE / "config" / "settings.json"
    }

    selector = ttk.Combobox(
        win, values=list(choices), state="readonly"
    )
    selector.pack(fill="x", padx=12)
    selector.current(0)

    editor = tk.Text(
        win, bg="#0c1220", fg="#d8eaff",
        insertbackground="white", font=("TkFixedFont", 10)
    )
    editor.pack(fill="both", expand=True, padx=12, pady=10)

    def load():
        path = choices[selector.get()]
        editor.delete("1.0", "end")
        if path.exists():
            editor.insert("1.0", path.read_text())

    def save():
        path = choices[selector.get()]
        content = editor.get("1.0", "end-1c")

        try:
            if path.suffix == ".json":
                json.loads(content)
            elif path.suffix == ".toml":
                import tomllib
                tomllib.loads(content)

            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(content)
            messagebox.showinfo("Settings", "Configuration saved.")
        except Exception as exc:
            messagebox.showerror("Invalid configuration", str(exc))

    selector.bind("<<ComboboxSelected>>", lambda event: load())
    button(win, "Load", load).pack(side="left", padx=12, pady=8)
    button(win, "Save", save).pack(side="left", pady=8)
    load()


# TERMINAL
def terminal(parent):
    win = window(parent, "Terminal", "750x500")

    label(win, "Termux command terminal").pack(pady=8)

    output = tk.Text(
        win, bg="#080d15", fg="#8aff9b",
        insertbackground="white", font=("TkFixedFont", 10)
    )
    output.pack(fill="both", expand=True, padx=10, pady=8)

    command = tk.Entry(win, font=("TkFixedFont", 11))
    command.pack(fill="x", padx=10)

    output.insert(
        "end",
        "MyLinux Terminal\n"
        f"Project: {PROJECT}\n"
        "Commands run with Termux user permissions.\n\n"
    )

    def execute(event=None):
        cmd = command.get().strip()
        if not cmd:
            return

        command.delete(0, "end")
        output.insert("end", f"\n$ {cmd}\n")
        output.see("end")

        def worker():
            try:
                result = subprocess.run(
                    cmd,
                    shell=True,
                    cwd=str(PROJECT),
                    text=True,
                    capture_output=True,
                    timeout=30
                )
                text = result.stdout + result.stderr
                if not text:
                    text = f"Exit code: {result.returncode}\n"

            except Exception as exc:
                text = str(exc) + "\n"

            win.after(
                0, lambda: (
                    output.insert("end", text),
                    output.see("end")
                )
            )

        threading.Thread(target=worker, daemon=True).start()

    command.bind("<Return>", execute)


# BROWSER
def browser(parent):
    win = window(parent, "Browser", "800x550")

    address = tk.Entry(win, font=("TkDefaultFont", 12))
    address.pack(fill="x", padx=12, pady=10)
    address.insert(0, "https://example.com")

    page = tk.Text(win, bg="#ffffff", fg="#111111", wrap="word")
    page.pack(fill="both", expand=True, padx=12, pady=8)

    def open_url():
        url = address.get().strip()
        if not url.startswith(("https://", "http://")):
            url = "https://" + url

        page.delete("1.0", "end")
        page.insert("end", "Loading...\n")

        def worker():
            try:
                request = urllib.request.Request(
                    url,
                    headers={"User-Agent": "MyLinuxBrowser/0.1"}
                )
                with urllib.request.urlopen(request, timeout=15) as response:
                    data = response.read(200000)
                    result = data.decode("utf-8", errors="replace")
            except Exception as exc:
                result = "Request failed: " + str(exc)

            win.after(
                0, lambda: (
                    page.delete("1.0", "end"),
                    page.insert("end", result)
                )
            )

        threading.Thread(target=worker, daemon=True).start()

    button(win, "Open URL", open_url).pack(pady=5)


# MYFILES
def files(parent, root_path=None):
    root_path = Path(root_path or PROJECT).resolve()
    win = window(parent, "MyFiles", "750x550")

    current = {"path": root_path}
    label_path = label(win, str(root_path))
    label_path.pack(pady=8)

    listing = tk.Listbox(
        win, bg="#0d1420", fg="white",
        font=("TkFixedFont", 11)
    )
    listing.pack(fill="both", expand=True, padx=12, pady=8)

    entries = []

    def refresh():
        listing.delete(0, "end")
        entries.clear()
        label_path.configure(text=str(current["path"]))

        try:
            for item in sorted(
                current["path"].iterdir(),
                key=lambda p: (not p.is_dir(), p.name.lower())
            ):
                entries.append(item)
                listing.insert(
                    "end",
                    ("[DIR] " if item.is_dir() else "[FILE] ") + item.name
                )
        except OSError as exc:
            messagebox.showerror("MyFiles", str(exc))

    def open_selected(event=None):
        selection = listing.curselection()
        if not selection:
            return

        item = entries[selection[0]]
        if item.is_dir():
            current["path"] = item.resolve()
            refresh()
        else:
            messagebox.showinfo("File", str(item))

    def up():
        if current["path"] == root_path:
            return
        parent_path = current["path"].parent
        if parent_path == root_path or root_path in parent_path.parents:
            current["path"] = parent_path
            refresh()

    listing.bind("<Double-Button-1>", open_selected)
    button(win, "Open directory", open_selected).pack(side="left", padx=10)
    button(win, "Up", up).pack(side="left")
    button(win, "Refresh", refresh).pack(side="left")
    refresh()


# HIDDEN ROOT EXPLORER
def root_explorer(parent):
    VROOT.mkdir(parents=True, exist_ok=True)
    files(parent, VROOT)


def open_app(parent, name):
    apps = {
        "Phone": phone,
        "Message": message,
        "Settings": settings,
        "Terminal": terminal,
        "Browser": browser,
        "MyFiles": files,
    }

    if name in apps:
        apps[name](parent)
    elif name == "System":
        win = window(parent, "System", "500x350")
        import platform
        import time

        info = (
            f"OS: {platform.system()}\n"
            f"Release: {platform.release()}\n"
            f"Machine: {platform.machine()}\n"
            f"Python: {sys.version}\n"
            f"Uptime counter: {time.monotonic():.2f}\n"
            f"Project: {PROJECT}\n"
        )
        label(win, info).pack(padx=15, pady=20)
