package network

import (
    "net"
    "time"
)

func TCPConnect(address string) (net.Conn, error) {
    return net.DialTimeout(
        "tcp",
        address,
        10*time.Second,
    )
}
