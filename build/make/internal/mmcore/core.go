package mmcore

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
)

type Config map[string]string

func FindTop(start string) (string, error) {
	if env := os.Getenv("MYLINUX_TOP"); env != "" {
		abs, err := filepath.Abs(env)
		if err == nil && isTop(abs) {
			return abs, nil
		}
	}

	current, err := filepath.Abs(start)
	if err != nil {
		return "", err
	}

	for {
		if isTop(current) {
			return current, nil
		}

		parent := filepath.Dir(current)
		if parent == current {
			break
		}
		current = parent
	}

	return "", fmt.Errorf("cannot find MyLinux project root")
}

func isTop(path string) bool {
	required := []string{
		"bionic",
		"frameworks",
		"build",
	}

	for _, name := range required {
		info, err := os.Stat(filepath.Join(path, name))
		if err != nil || !info.IsDir() {
			return false
		}
	}

	return true
}

func LoadConfig(top, mode string) (Config, error) {
	path := filepath.Join(top, "build", "make", "config", mode+".mod")
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	config := make(Config)
	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())

		if line == "" || strings.HasPrefix(line, "#") {
			continue
		}

		key, value, found := strings.Cut(line, "=")
		if !found {
			continue
		}

		config[strings.TrimSpace(key)] = strings.TrimSpace(value)
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}

	if config["MODULE"] != mode {
		return nil, fmt.Errorf("invalid configuration for %s", mode)
	}

	return config, nil
}

func insideTop(top, path string) bool {
	rel, err := filepath.Rel(top, path)
	if err != nil {
		return false
	}
	return rel != ".." &&
		!strings.HasPrefix(rel, ".."+string(os.PathSeparator))
}

func resolveDirectory(top, current, value string) (string, error) {
	var path string

	if filepath.IsAbs(value) {
		path = value
	} else {
		path = filepath.Join(current, value)
	}

	path, err := filepath.Abs(path)
	if err != nil {
		return "", err
	}

	info, err := os.Stat(path)
	if err != nil {
		return "", err
	}
	if !info.IsDir() {
		return "", fmt.Errorf("%s is not a directory", path)
	}
	if !insideTop(top, path) {
		return "", fmt.Errorf("%s is outside the MyLinux tree", path)
	}

	return path, nil
}

func buildDirectory(dir string, args []string) error {
	ninjaFile := filepath.Join(dir, "build.ninja")
	makeFile := filepath.Join(dir, "Makefile")

	if _, err := os.Stat(ninjaFile); err == nil {
		commandArgs := []string{"-C", dir}
		commandArgs = append(commandArgs, args...)
		return runCommand("ninja", commandArgs...)
	}

	if _, err := os.Stat(makeFile); err == nil {
		commandArgs := []string{"-C", dir}
		commandArgs = append(commandArgs, args...)
		return runCommand("make", commandArgs...)
	}

	if _, err := os.Stat(filepath.Join(dir, "Android.bp")); err == nil {
		return fmt.Errorf(
			"%s contains Android.bp but has no generated Ninja build file; Soong is not implemented here",
			dir,
		)
	}

	return fmt.Errorf("%s has no build.ninja or Makefile", dir)
}

func runCommand(name string, args ...string) error {
	fmt.Printf("\n[MYLINUX] Running: %s %s\n", name, strings.Join(args, " "))

	command := exec.Command(name, args...)
	command.Stdout = os.Stdout
	command.Stderr = os.Stderr
	command.Stdin = os.Stdin

	return command.Run()
}

func recursiveModules(top, start string) ([]string, error) {
	var modules []string

	skip := map[string]bool{
		".git":      true,
		".repo":     true,
		"out":       true,
		"prebuilts": true,
	}

	err := filepath.WalkDir(start, func(
		path string,
		entry os.DirEntry,
		err error,
	) error {
		if err != nil {
			return err
		}

		if entry.IsDir() && path != start && skip[entry.Name()] {
			return filepath.SkipDir
		}

		if !entry.IsDir() {
			return nil
		}

		if _, err := os.Stat(filepath.Join(path, "build.ninja")); err == nil {
			modules = append(modules, path)
			return nil
		}

		if _, err := os.Stat(filepath.Join(path, "Makefile")); err == nil {
			modules = append(modules, path)
		}

		return nil
	})

	return modules, err
}

func Execute(mode string, args []string) int {
	cwd, err := os.Getwd()
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		return 1
	}

	top, err := FindTop(cwd)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		return 1
	}

	if mode == "gettop" {
		fmt.Println(top)
		return 0
	}

	config, err := LoadConfig(top, mode)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		return 1
	}

	fmt.Printf("[MYLINUX] Command: %s\n", mode)
	fmt.Printf("[MYLINUX] Project: %s\n", top)

	switch mode {
	case "m":
		return runWholeTree(top, args)

	case "mm":
		dir, err := resolveDirectory(top, cwd, ".")
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			return 1
		}
		return reportBuild(dir, args)

	case "mmm":
		return runSpecified(top, cwd, args)

	case "mmma":
		return runRecursive(top, cwd, args)

	default:
		fmt.Fprintf(os.Stderr, "unknown command: %s\n", mode)
		return 1
	}

	_ = config
}

func reportBuild(dir string, args []string) int {
	fmt.Printf("[MYLINUX] Building: %s\n", dir)

	if err := buildDirectory(dir, args); err != nil {
		fmt.Fprintln(os.Stderr, "[MYLINUX] Build failed:", err)
		return 1
	}

	fmt.Println("[MYLINUX] Build completed:", dir)
	return 0
}

func runWholeTree(top string, args []string) int {
	// Prefer a generated whole-tree Ninja build.
	candidates := []string{
		filepath.Join(top, "out", "build.ninja"),
		filepath.Join(top, "build.ninja"),
	}

	for _, candidate := range candidates {
		if _, err := os.Stat(candidate); err == nil {
			fmt.Println("[MYLINUX] Using:", candidate)
			return reportNinjaFile(top, candidate, args)
		}
	}

	if _, err := os.Stat(filepath.Join(top, "Makefile")); err == nil {
		return reportBuild(top, args)
	}

	fmt.Fprintln(os.Stderr,
		"[MYLINUX] No whole-tree build file found.")
	fmt.Fprintln(os.Stderr,
		"[MYLINUX] Generate out/build.ninja or add a root Makefile first.")
	return 1
}

func reportNinjaFile(top, file string, args []string) int {
	rel, err := filepath.Rel(top, file)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		return 1
	}

	commandArgs := []string{"-C", top, "-f", rel}
	commandArgs = append(commandArgs, args...)

	if err := runCommand("ninja", commandArgs...); err != nil {
		fmt.Fprintln(os.Stderr, "[MYLINUX] Build failed:", err)
		return 1
	}

	fmt.Println("[MYLINUX] Whole-tree build completed.")
	return 0
}

func runSpecified(top, cwd string, args []string) int {
	if len(args) == 0 {
		fmt.Fprintln(os.Stderr, "usage: mmm directory [directory ...]")
		return 2
	}

	failed := false

	for _, value := range args {
		dir, err := resolveDirectory(top, cwd, value)
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			failed = true
			continue
		}

		if reportBuild(dir, nil) != 0 {
			failed = true
		}
	}

	if failed {
		return 1
	}
	return 0
}

func runRecursive(top, cwd string, args []string) int {
	if len(args) == 0 {
		fmt.Fprintln(os.Stderr, "usage: mmma directory [directory ...]")
		return 2
	}

	failed := false

	for _, value := range args {
		start, err := resolveDirectory(top, cwd, value)
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			failed = true
			continue
		}

		modules, err := recursiveModules(top, start)
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			failed = true
			continue
		}

		for _, dir := range modules {
			if reportBuild(dir, nil) != 0 {
				failed = true
			}
		}
	}

	if failed {
		return 1
	}
	return 0
}
