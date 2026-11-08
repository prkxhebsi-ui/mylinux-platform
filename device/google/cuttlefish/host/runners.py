import argparse
import configparser
import re
import sys
import tomllib
from pathlib import Path


def run_mk(path):
    print("MyLinux Android Makefile inspector")
    print("File:", path)

    assignment = re.compile(
        r"^\s*([A-Za-z0-9_.-]+)\s*(\+=|:=|\?=|=)\s*(.*?)\s*$"
    )

    target = re.compile(
        r"^\s*([A-Za-z0-9_.-]+)\s*:\s*(.*?)\s*$"
    )

    for number, line in enumerate(
        path.read_text(errors="replace").splitlines(), 1
    ):
        stripped = line.strip()

        if not stripped or stripped.startswith("#"):
            continue

        match = assignment.match(line)
        if match:
            print(
                f"Line {number}: variable {match.group(1)} "
                f"{match.group(2)} {match.group(3)}"
            )
            continue

        match = target.match(line)
        if match:
            print(
                f"Line {number}: target {match.group(1)} "
                f"dependencies: {match.group(2)}"
            )
            continue

        if line.startswith((" ", "\t")):
            print(f"Line {number}: recipe (not executed)")
        else:
            print(f"Line {number}: unrecognized Make syntax")

    print("\nInspection complete. No recipes were executed.")


def run_conf(path):
    print("MyLinux INI configuration inspector")
    parser = configparser.ConfigParser()
    parser.read(path)

    for section in parser.sections():
        print(f"\n[{section}]")
        for key, value in parser.items(section):
            print(f"{key} = {value}")

    print("\nConfiguration parsed successfully.")


def run_rc(path):
    print("MyLinux Android init.rc inspector")
    section = None

    for number, line in enumerate(
        path.read_text(errors="replace").splitlines(), 1
    ):
        stripped = line.strip()

        if not stripped or stripped.startswith("#"):
            continue

        if stripped.startswith("service "):
            section = stripped
            print(f"\nLine {number}: SERVICE {stripped[8:]}")
        elif stripped.startswith("on "):
            section = stripped
            print(f"\nLine {number}: ACTION {stripped[3:]}")
        elif stripped.startswith("import "):
            print(f"Line {number}: IMPORT {stripped[7:]}")
        elif section:
            print(f"  Line {number}: {stripped}")
        else:
            print(f"Line {number}: directive {stripped}")

    print("\nInspection complete. No init commands were executed.")


def main():
    parser = argparse.ArgumentParser(
        description="MyLinux configuration runners"
    )
    parser.add_argument("file", type=Path)
    args = parser.parse_args()

    path = args.file

    if not path.is_file():
        print("File not found:", path)
        return 1

    suffix = path.suffix.lower()

    try:
        if suffix == ".mk":
            run_mk(path)
        elif suffix == ".conf":
            run_conf(path)
        elif suffix == ".rc":
            run_rc(path)
        elif suffix == ".toml":
            with path.open("rb") as file:
                tomllib.load(file)
            print("TOML configuration valid:", path)
        else:
            print("Unsupported configuration extension:", suffix)
            return 2

    except Exception as exc:
        print("Configuration error:", exc)
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
