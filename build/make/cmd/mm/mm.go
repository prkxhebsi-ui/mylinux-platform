package main

import (
	"os"

	"mylinux/buildmake/internal/mmcore"
)

func main() {
	os.Exit(mmcore.Execute("mm", os.Args[1:]))
}
