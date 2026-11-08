package android

import (
	"fmt"
	"path/filepath"
)

type Module struct {
	Name      string
	Type      string
	Dir       string
	Blueprint string

	Srcs       []string
	Deps       []string
	Cflags     []string
	Enabled    bool
	Properties map[string]any
}

type Registry struct {
	modules map[string]*Module
}

func NewRegistry() *Registry {
	return &Registry{
		modules: make(map[string]*Module),
	}
}

func (r *Registry) Add(m *Module) error {
	if m == nil {
		return fmt.Errorf("cannot register nil module")
	}

	if m.Name == "" {
		return fmt.Errorf("module has no name")
	}

	if _, exists := r.modules[m.Name]; exists {
		return fmt.Errorf("duplicate module: %s", m.Name)
	}

	r.modules[m.Name] = m
	return nil
}

func (r *Registry) Get(name string) (*Module, bool) {
	m, ok := r.modules[name]
	return m, ok
}

func (r *Registry) All() []*Module {
	result := make([]*Module, 0, len(r.modules))

	for _, m := range r.modules {
		result = append(result, m)
	}

	return result
}

func (m *Module) SourcePaths() []string {
	result := make([]string, 0, len(m.Srcs))

	for _, src := range m.Srcs {
		if filepath.IsAbs(src) {
			result = append(result, src)
		} else {
			result = append(result, filepath.Join(m.Dir, src))
		}
	}

	return result
}
