package android

import (
	"fmt"
	"sort"
)

func BuildOrder(registry *Registry) ([]*Module, error) {
	modules := registry.All()

	sort.Slice(modules, func(i, j int) bool {
		return modules[i].Name < modules[j].Name
	})

	const (
		unvisited = 0
		visiting  = 1
		visited   = 2
	)

	state := make(map[string]int)
	var order []*Module
	var visit func(string) error

	visit = func(name string) error {
		switch state[name] {
		case visiting:
			return fmt.Errorf("dependency cycle detected at %s", name)
		case visited:
			return nil
		}

		m, exists := registry.Get(name)
		if !exists {
			return fmt.Errorf("missing dependency: %s", name)
		}

		state[name] = visiting

		deps := append([]string(nil), m.Deps...)
		sort.Strings(deps)

		for _, dep := range deps {
			if _, exists := registry.Get(dep); !exists {
				return fmt.Errorf(
					"module %s requires unknown module %s",
					name, dep,
				)
			}

			if err := visit(dep); err != nil {
				return err
			}
		}

		state[name] = visited
		if m.Enabled {
			order = append(order, m)
		}

		return nil
	}

	for _, m := range modules {
		if err := visit(m.Name); err != nil {
			return nil, err
		}
	}

	return order, nil
}
