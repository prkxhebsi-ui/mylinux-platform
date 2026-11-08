package network

import "net"

func UDPConnect(address string) (net.Conn, error) {
    return net.Dial("udp", address)
}
