package main

import (
	"os"

	"mylinux/buildmake/internal/mmcore"
)

func main() {
	os.Exit(mmcore.Execute("m", os.Args[1:]))
}
