package connman

import (
	"bufio"
	"net"
	"time"
)

const availablePrefetch = 16

type buffConn struct {
	valid    bool
	r        *bufio.Reader
	net.Conn // So that most methods are embedded
}

func newBufferedConn(c net.Conn) buffConn {
	return buffConn{true, bufio.NewReader(c), c}
}

func (b buffConn) Available() int {
	if b.r.Buffered() > 0 {
		return b.r.Buffered()
	}

	_ = b.SetReadDeadline(time.Now().Add(time.Millisecond * 1))
	_, _ = b.Peek(availablePrefetch)

	return b.r.Buffered()
}

func (b buffConn) Peek(n int) ([]byte, error) {
	return b.r.Peek(n)
}

func (b buffConn) Read(p []byte) (int, error) {
	return b.r.Read(p)
}
