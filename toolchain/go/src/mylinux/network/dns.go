package network

import "net"

func DNSLookup(host string) ([]string, error) {
    return net.LookupHost(host)
}
