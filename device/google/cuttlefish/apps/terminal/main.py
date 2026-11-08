import tkinter as tk
from tkinter import ttk
from pathlib import Path
import os
import sys
import shlex
import stat
import socket
import tempfile
import subprocess
import threading


def launch(parent):
    root = tk.Toplevel(parent)
    root.title("MyLinux Terminal")
    root.geometry("850x550")
    root.configure(bg="#101522")

    cwd = Path.home() / "roms" / "mylinux-platform"
    cwd = cwd.resolve()

    sockets = []

    output = tk.Text(
        root,
        bg="#080d15",
        fg="white",
        insertbackground="white",
        font=("TkFixedFont", 11),
        wrap="none"
    )
    output.pack(fill="both", expand=True, padx=8, pady=8)

    output.tag_configure("directory", foreground="#c080ff")
    output.tag_configure("socket", foreground="#c080ff")
    output.tag_configure("file", foreground="#ffffff")
    output.tag_configure("link", foreground="#ffd166")
    output.tag_configure("error", foreground="#ff6666")
    output.tag_configure("success", foreground="#80ff9c")
    output.tag_configure("prompt", foreground="#66ccff")

    command = tk.Entry(
        root,
        bg="#202b40",
        fg="white",
        insertbackground="white",
        font=("TkFixedFont", 12)
    )
    command.pack(fill="x", padx=8, pady=(0, 8))

    def write(text, tag=None):
        output.insert("end", text, tag)
        output.see("end")

    def resolve(value):
        path = Path(value).expanduser()
        if not path.is_absolute():
            path = cwd / path
        return path

    def show_ls(path):
        try:
            entries = sorted(
                path.iterdir(),
                key=lambda item: (not item.is_dir(), item.name.lower())
            )

            for item in entries:
                try:
                    mode = item.lstat().st_mode

                    if stat.S_ISSOCK(mode):
                        tag = "socket"
                        suffix = " [SOCKET]"
                    elif stat.S_ISDIR(mode):
                        tag = "directory"
                        suffix = "/"
                    elif stat.S_ISLNK(mode):
                        tag = "link"
                        suffix = "@"
                    else:
                        tag = "file"
                        suffix = ""

                    write(item.name + suffix + "\n", tag)

                except OSError:
                    write(item.name + "\n", "file")

        except OSError as exc:
            write(str(exc) + "\n", "error")

    def execute(line):
        nonlocal cwd

        try:
            args = shlex.split(line)
        except ValueError as exc:
            write(str(exc) + "\n", "error")
            return

        if not args:
            return

        cmd = args[0]
        argv = args[1:]

        try:
            # LS
            if cmd == "ls":
                path = resolve(argv[0]) if argv else cwd
                show_ls(path)

            # CD
            elif cmd == "cd":
                target = resolve(argv[0]) if argv else Path.home()
                if target.is_dir():
                    cwd = target.resolve()
                else:
                    raise NotADirectoryError(str(target))

            # MKDIR
            elif cmd == "mkdir":
                if not argv:
                    raise ValueError("usage: mkdir DIRECTORY")
                for item in argv:
                    resolve(item).mkdir()

            # MKPATH: recursive mkdir
            elif cmd == "mkpath":
                if not argv:
                    raise ValueError("usage: mkpath DIRECTORY")
                for item in argv:
                    resolve(item).mkdir(parents=True, exist_ok=True)

            # MKLOST+FOUND
            elif cmd == "mklost+found":
                target = resolve(argv[0]) if argv else cwd / "lost+found"
                target.mkdir(parents=True, exist_ok=True)
                write("Created " + str(target) + "\n", "success")

            # MKTEMP
            elif cmd == "mktemp":
                directory = resolve(argv[0]) if argv else cwd
                fd, name = tempfile.mkstemp(dir=directory)
                os.close(fd)
                write(name + "\n", "success")

            # LN
            elif cmd == "ln":
                symbolic = False
                if argv and argv[0] == "-s":
                    symbolic = True
                    argv = argv[1:]

                if len(argv) != 2:
                    raise ValueError("usage: ln [-s] TARGET LINK")

                source = resolve(argv[0])
                destination = resolve(argv[1])

                if symbolic:
                    os.symlink(source, destination)
                else:
                    os.link(source, destination)

            # SOCKET
            elif cmd == "socket":
                if len(argv) != 1:
                    raise ValueError("usage: socket PATH")

                path = resolve(argv[0])
                path.parent.mkdir(parents=True, exist_ok=True)

                sock = socket.socket(
                    socket.AF_UNIX,
                    socket.SOCK_STREAM
                )
                sock.bind(str(path))
                sockets.append(sock)

                write("Unix socket created: " + str(path) + "\n", "success")

            # MKNOD: safe regular-file placeholder only
            elif cmd == "mknod":
                if len(argv) != 1:
                    raise ValueError("usage: mknod PATH")

                path = resolve(argv[0])
                path.parent.mkdir(parents=True, exist_ok=True)
                path.touch(exist_ok=False)

                write(
                    "Created ordinary file (not a device node): "
                    + str(path) + "\n",
                    "success"
                )

            # MKE2FS: deliberately disabled
            elif cmd == "mke2fs":
                write(
                    "mke2fs: disabled in MyLinux desktop. "
                    "Filesystem formatting is destructive.\n",
                    "error"
                )

            # PWD
            elif cmd == "pwd":
                write(str(cwd) + "\n", "success")

            # CLEAR
            elif cmd == "clear":
                output.delete("1.0", "end")

            # HELP
            elif cmd in ("help", "?"):
                write(
                    "MyLinux built-in commands:\n"
                    "  ls             List files\n"
                    "  cd PATH        Change directory\n"
                    "  pwd            Print current directory\n"
                    "  mkdir DIR      Create directory\n"
                    "  mkpath DIR     Create directory parents\n"
                    "  mktemp [DIR]   Create temporary file\n"
                    "  mklost+found   Create lost+found directory\n"
                    "  ln [-s] A B    Create link\n"
                    "  socket PATH    Create Unix socket\n"
                    "  mknod PATH     Create ordinary placeholder file\n"
                    "  clear          Clear terminal\n"
                    "  help           Show this help\n"
                    "  exit           Close terminal\n"
                    "  mke2fs         Disabled for safety\n\n"
                )

            # EXIT
            elif cmd == "exit":
                root.destroy()
                return

            # EXTERNAL TERMUX COMMAND
            else:
                result = subprocess.run(
                    args,
                    cwd=str(cwd),
                    text=True,
                    capture_output=True,
                    timeout=30
                )

                if result.stdout:
                    write(result.stdout)

                if result.stderr:
                    write(result.stderr, "error")

                if result.returncode:
                    write(
                        "Exit code: " + str(result.returncode) + "\n",
                        "error"
                    )

        except Exception as exc:
            write(str(exc) + "\n", "error")

    def submit(event=None):
        line = command.get()
        command.delete(0, "end")

        write(str(cwd) + " $ " + line + "\n", "prompt")
        execute(line)

    def close():
        for sock in sockets:
            try:
                sock.close()
            except OSError:
                pass
        root.destroy()

    command.bind("<Return>", submit)
    root.protocol("WM_DELETE_WINDOW", close)

    write("MyLinux Terminal 0.2\n", "success")
    write("Type help to see available commands.\n\n")
    write(str(cwd) + "\n", "prompt")

    command.focus_set()
    return root
