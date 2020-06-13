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
	timeout  uint64
}

func newBufferedConn(c net.Conn) *buffConn {
	return &buffConn{
		valid:   true,
		r:       bufio.NewReader(c),
		Conn:    c,
		timeout: uint64(time.Second),
	}
}

func (b *buffConn) SetTimeout(millis uint64) {
	b.timeout = millis
}

func (b *buffConn) Available() int {
	if b.r.Buffered() > 0 {
		return b.r.Buffered()
	}

	_ = b.SetReadDeadline(time.Now().Add(time.Millisecond * 1))
	_, _ = b.Peek(availablePrefetch)

	return b.r.Buffered()
}

func (b *buffConn) Peek(n int) ([]byte, error) {
	return b.r.Peek(n)
}

func (b *buffConn) Read(p []byte) (int, error) {
	_ = b.SetReadDeadline(time.Now().Add(time.Millisecond * time.Duration(b.timeout)))
	return b.r.Read(p)
}
