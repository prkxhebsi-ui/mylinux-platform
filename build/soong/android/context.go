package android

import (
	"fmt"
	"io/fs"
	"os"
	"path/filepath"
	"strings"
)

type Context struct {
	Config   *Config
	Registry *Registry
}

func NewContext(config *Config) *Context {
	return &Context{
		Config:   config,
		Registry: NewRegistry(),
	}
}

func (c *Context) Load() error {
	return filepath.WalkDir(c.Config.Top, func(
		path string,
		entry fs.DirEntry,
		walkErr error,
	) error {
		if walkErr != nil {
			return walkErr
		}

		if entry.IsDir() {
			switch entry.Name() {
			case ".git", ".repo", "out", ".gradle":
				return filepath.SkipDir
			}
			return nil
		}

		if entry.Name() != "Android.bp" {
			return nil
		}

		// Do not parse generated output files.
		rel, err := filepath.Rel(c.Config.Top, path)
		if err != nil {
			return err
		}

		if strings.HasPrefix(rel, "..") {
			return nil
		}

		modules, err := ParseFile(path)
		if err != nil {
			return fmt.Errorf("%s: %w", path, err)
		}

		dir := filepath.Dir(path)

		for _, m := range modules {
			m.Dir = dir
			m.Blueprint = path

			if err := c.Registry.Add(m); err != nil {
				return fmt.Errorf("%s: %w", path, err)
			}
		}

		return nil
	})
}

func EnsureDirectory(path string) error {
	return os.MkdirAll(path, 0755)
}
