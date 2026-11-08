package network

import (
    "mylinux/features"
    "mylinux/netbase"
)

func Version() string {
    return netbase.NetworkVersion()
}

func AddNetworkValues(a, b int) int {
    return features.Add(a, b)
}

func CheckPort(port int) bool {
    return netbase.IsValidPort(port)
}

func CheckHTTP(url string) bool {
    return netbase.IsHTTP(url)
}

func CheckHTTPS(url string) bool {
    return netbase.IsHTTPS(url)
}

func PrintNetworkInfo() {
    println(Version())
    println("HTTP port:", netbase.DefaultHTTPPort)
    println("HTTPS port:", netbase.DefaultHTTPSPort)
}
