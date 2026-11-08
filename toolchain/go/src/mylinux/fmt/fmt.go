package mylinuxfmt

import (
    "mylinux/features"
    "mylinux/net/netbase"
    myos "mylinux/os"
)

// MyLinux formatting system
const FormatVersion = 1

var FormatName = "MyLinux Format"

// Print general information
func PrintSystem() {
    println("=== MyLinux System ===")
    println("Format:", FormatName)
    println("Version:", FormatVersion)
}

// Use features package
func PrintFeatures() {
    println("=== Features ===")
    println("Addition:", features.Add(10, 20))
    features.PrintExample()
}

// Use netbase package
func PrintNetwork() {
    println("=== Network ===")

    stack := netbase.NewStack()
    stack.Start()
    stack.PrintInfo()
    stack.Stop()
}

// Use OS package
func PrintOS() {
    println("=== Operating System ===")

    system := myos.NewSystem("mylinux-device")
    system.Start()
    system.PrintInfo()
    system.Stop()
}

// Print everything
func PrintAll() {
    PrintSystem()
    PrintFeatures()
    PrintNetwork()
    PrintOS()
}
