package main

import (
	"flag"
	"fmt"
	"os"
	"path/filepath"

	"mylinux/soong/android"
)

func main() {
	top := flag.String("top", ".", "MyLinux source root")
	out := flag.String("out", "out", "Build output directory")
	product := flag.String("product", "mylinux_gto", "Target product")
	variant := flag.String("variant", "userdebug", "Build variant")

	flag.Parse()

	config, err := android.NewConfig(
		*top,
		*out,
		*product,
		*variant,
	)
	if err != nil {
		fatal(err)
	}

	fmt.Println("====================================")
	fmt.Println(" MyLinux Soong Build Engine")
	fmt.Println("====================================")
	fmt.Println("TOP:     ", config.Top)
	fmt.Println("OUT:     ", config.Out)
	fmt.Println("PRODUCT: ", config.Product)
	fmt.Println("VARIANT: ", config.Variant)
	fmt.Println("ARCH:    ", config.Arch)

	ctx := android.NewContext(config)

	fmt.Println("\nScanning Android.bp files...")

	if err := ctx.Load(); err != nil {
		fatal(err)
	}

	modules := ctx.Registry.All()

	fmt.Printf("Discovered modules: %d\n", len(modules))

	fmt.Println("\nResolving dependencies...")

	order, err := android.BuildOrder(ctx.Registry)
	if err != nil {
		fatal(err)
	}

	fmt.Printf("Resolved modules: %d\n", len(order))

	fmt.Println("\nBuild order:")

	for i, module := range order {
		fmt.Printf(
			"%04d  %-24s [%s]\n",
			i+1,
			module.Name,
			module.Type,
		)
	}

	outputDir := filepath.Join(config.Out, "soong")

	if err := os.MkdirAll(outputDir, 0755); err != nil {
		fatal(err)
	}

	graphPath := filepath.Join(outputDir, "module-graph.txt")

	file, err := os.Create(graphPath)
	if err != nil {
		fatal(err)
	}

	for _, module := range order {
		fmt.Fprintf(
			file,
			"%s [%s]\n",
			module.Name,
			module.Type,
		)

		for _, dep := range module.Deps {
			fmt.Fprintf(file, "  -> %s\n", dep)
		}
	}

	if err := file.Close(); err != nil {
		fatal(err)
	}

	fmt.Println("\nSoong analysis completed.")
	fmt.Println("Module graph:", graphPath)
}

func fatal(err error) {
	fmt.Fprintln(os.Stderr, "soong_build:", err)
	os.Exit(1)
}
