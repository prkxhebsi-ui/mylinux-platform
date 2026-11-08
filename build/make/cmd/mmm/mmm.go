package main

import (
	"os"

	"mylinux/buildmake/internal/mmcore"
)

func main() {
	os.Exit(mmcore.Execute("mmm", os.Args[1:]))
}
