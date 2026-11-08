package main

import (
	"os"

	"mylinux/buildmake/internal/mmcore"
)

func main() {
	os.Exit(mmcore.Execute("mmma", os.Args[1:]))
}
