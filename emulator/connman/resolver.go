package connman

import (
	"fmt"
	"net"
)

// ResolveAddr resolves an hostname or ip to a net.IP object
func ResolveAddr(host string) net.IP {
	if host == "" {
		return nil
	}

	ip := net.ParseIP(host)

	if ip == nil {
		ips, err := net.LookupIP(host)
		if err != nil {
			fmt.Printf("cannot resolve address %q: %s\n", host, err)
			return nil
		}
		if len(ips) == 0 {
			fmt.Printf("no address associated to %s\n", host)
			return nil
		}

		ip = ips[0]
	}

	return ip
}
