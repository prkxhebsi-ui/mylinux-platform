package android

import "testing"

func TestParseModules(t *testing.T) {
	source := `
cc_library {
    name: "libtest",
    srcs: ["test.c"],
    cflags: ["-Wall"],
}

cc_binary {
    name: "test_app",
    shared_libs: ["libtest"],
}
`

	modules, err := Parse(source)
	if err != nil {
		t.Fatal(err)
	}

	if len(modules) != 2 {
		t.Fatalf("expected 2 modules, got %d", len(modules))
	}

	if modules[0].Name != "libtest" {
		t.Fatalf("unexpected module: %s", modules[0].Name)
	}

	if len(modules[1].Deps) != 1 {
		t.Fatal("dependency was not parsed")
	}
}

func TestDependencyOrder(t *testing.T) {
	registry := NewRegistry()

	lib := &Module{Name: "lib", Enabled: true}
	app := &Module{
		Name:    "app",
		Deps:    []string{"lib"},
		Enabled: true,
	}

	if err := registry.Add(app); err != nil {
		t.Fatal(err)
	}

	if err := registry.Add(lib); err != nil {
		t.Fatal(err)
	}

	order, err := BuildOrder(registry)
	if err != nil {
		t.Fatal(err)
	}

	if len(order) != 2 {
		t.Fatalf("expected 2 modules, got %d", len(order))
	}

	if order[0].Name != "lib" || order[1].Name != "app" {
		t.Fatal("incorrect dependency order")
	}
}

func TestDependencyCycle(t *testing.T) {
	registry := NewRegistry()

	registry.Add(&Module{
		Name: "a",
		Deps: []string{"b"},
	})

	registry.Add(&Module{
		Name: "b",
		Deps: []string{"a"},
	})

	_, err := BuildOrder(registry)
	if err == nil {
		t.Fatal("expected dependency cycle error")
	}
}
