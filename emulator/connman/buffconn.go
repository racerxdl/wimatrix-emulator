package connman

import (
	"bufio"
	"fmt"
	"net"
	"time"
)

const availablePrefetch = 16

type buffConn struct {
	valid   bool
	r       *bufio.Reader
	conn    net.Conn // So that most methods are embedded
	timeout uint64
	isUdp   bool
	u       *net.UDPConn
}

func newBufferedConn(c net.Conn) *buffConn {
	return &buffConn{
		valid:   true,
		r:       bufio.NewReader(c),
		conn:    c,
		timeout: uint64(time.Second),
		isUdp:   false,
	}
}

func newBufferedUDPConn(c *net.UDPConn) *buffConn {
	return &buffConn{
		valid:   true,
		r:       bufio.NewReader(c),
		conn:    c,
		u:       c,
		timeout: uint64(time.Second),
		isUdp:   true,
	}
}

func (b *buffConn) SetTimeout(millis uint64) {
	b.timeout = millis
}

func (b *buffConn) Available() int {
	if b.r.Buffered() > 0 {
		return b.r.Buffered()
	}

	_ = b.conn.SetReadDeadline(time.Now().Add(time.Millisecond * 1))
	_, _ = b.Peek(availablePrefetch)

	return b.r.Buffered()
}

func (b *buffConn) Peek(n int) ([]byte, error) {
	return b.r.Peek(n)
}

func (b *buffConn) Read(p []byte) (int, error) {
	_ = b.conn.SetReadDeadline(time.Now().Add(time.Millisecond * time.Duration(b.timeout)))
	return b.r.Read(p)
}

func (b *buffConn) ReadPacket() ([]byte, *net.UDPAddr, error) {
	if !b.isUdp {
		return nil, nil, fmt.Errorf("not an udp socket")
	}

	buff := make([]byte, 1460)
	n, addr, err := b.ReadFrom(buff)
	return buff[:n], addr, err
}

func (b *buffConn) WriteTo(host string, port int, data []byte) (int, error) {
	if !b.isUdp {
		return 0, fmt.Errorf("not an udp socket")
	}

	ip := ResolveAddr(host)

	if ip == nil {
		return 0, fmt.Errorf("cannot parse host %q", host)
	}

	addr := &net.UDPAddr{
		Port: port,
		IP:   ip,
	}

	fmt.Printf("Writing %d bytes to %s:%d\n", len(data), ip.String(), port)
	return b.u.WriteToUDP(data, addr)
}

func (b *buffConn) ReadFrom(data []byte) (int, *net.UDPAddr, error) {
	if !b.isUdp {
		return 0, nil, fmt.Errorf("not an udp socket")
	}

	_ = b.u.SetReadDeadline(time.Now().Add(time.Millisecond * time.Duration(b.timeout)))
	return b.u.ReadFromUDP(data)
}

// Write writes data to the connection.
// Write can be made to time out and return an Error with Timeout() == true
// after a fixed time limit; see SetDeadline and SetWriteDeadline.
func (b *buffConn) Write(data []byte) (n int, err error) {
	return b.conn.Write(data)
}

// Close closes the connection.
// Any blocked Read or Write operations will be unblocked and return errors.
func (b *buffConn) Close() error {
	return b.conn.Close()
}

// LocalAddr returns the local network address.
func (b *buffConn) LocalAddr() net.Addr {
	return b.conn.LocalAddr()
}

// RemoteAddr returns the remote network address.
func (b *buffConn) RemoteAddr() net.Addr {
	return b.conn.RemoteAddr()
}

// SetDeadline sets the read and write deadlines associated
// with the connection. It is equivalent to calling both
// SetReadDeadline and SetWriteDeadline.
//
// A deadline is an absolute time after which I/O operations
// fail with a timeout (see type Error) instead of
// blocking. The deadline applies to all future and pending
// I/O, not just the immediately following call to Read or
// Write. After a deadline has been exceeded, the connection
// can be refreshed by setting a deadline in the future.
//
// An idle timeout can be implemented by repeatedly extending
// the deadline after successful Read or Write calls.
//
// A zero value for t means I/O operations will not time out.
//
// Note that if a TCP connection has keep-alive turned on,
// which is the default unless overridden by Dialer.KeepAlive
// or ListenConfig.KeepAlive, then a keep-alive failure may
// also return a timeout error. On Unix systems a keep-alive
// failure on I/O can be detected using
// errors.Is(err, syscall.ETIMEDOUT).
func (b *buffConn) SetDeadline(t time.Time) error {
	return b.conn.SetDeadline(t)
}

// SetReadDeadline sets the deadline for future Read calls
// and any currently-blocked Read call.
// A zero value for t means Read will not time out.
func (b *buffConn) SetReadDeadline(t time.Time) error {
	return b.SetReadDeadline(t)
}

// SetWriteDeadline sets the deadline for future Write calls
// and any currently-blocked Write call.
// Even if write times out, it may return n > 0, indicating that
// some of the data was successfully written.
// A zero value for t means Write will not time out.
func (b *buffConn) SetWriteDeadline(t time.Time) error {
	return b.conn.SetWriteDeadline(t)
}
