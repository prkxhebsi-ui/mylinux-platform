package android

import (
	"fmt"
	"os"
	"path/filepath"
)

type Config struct {
	Top            string
	Out            string
	Product        string
	Variant        string
	Arch           string
	AndroidVersion string
}

func NewConfig(top, out, product, variant string) (*Config, error) {
	if top == "" {
		return nil, fmt.Errorf("source root is required")
	}

	absTop, err := filepath.Abs(top)
	if err != nil {
		return nil, err
	}

	absOut, err := filepath.Abs(out)
	if err != nil {
		return nil, err
	}

	if product == "" {
		product = "mylinux_gto"
	}

	if variant == "" {
		variant = "userdebug"
	}

	switch variant {
	case "user", "userdebug", "eng":
	default:
		return nil, fmt.Errorf("invalid build variant: %s", variant)
	}

	if err := os.MkdirAll(absOut, 0755); err != nil {
		return nil, err
	}

	return &Config{
		Top:            absTop,
		Out:            absOut,
		Product:        product,
		Variant:        variant,
		Arch:           "arm64",
		AndroidVersion: "11",
	}, nil
}
