package connman

import (
	"fmt"
	"net"
	"sync"
)

type ConnectionOpener interface {
	Open(host string, port int) (fd int, err error)
	OpenUDP(host string, port int) (fd int, err error)
}

type FdReader interface {
	Read(fd int, data []byte) (n int, err error)
	Peek(fd, n int) ([]byte, error)
	Available(fd int) (int, error)
	SetTimeout(fd int, millis uint64) error
	ReadPacket(fd int) ([]byte, *net.UDPAddr, error)
}

type FdWriter interface {
	Write(fd int, data []byte) (n int, err error)
	WriteTo(fd int, host string, port int, data []byte) (int, error)
}

type FdCloser interface {
	Close(fd int) error
}

type Manager interface {
	ConnectionOpener
	FdReader
	FdCloser
	FdWriter
}

type connman struct {
	lock           sync.Mutex
	connectionList map[int]*buffConn
	lastConn       int
	freeNumber     []int
}

func MakeManager() Manager {
	return &connman{
		lock:           sync.Mutex{},
		lastConn:       -1,
		connectionList: make(map[int]*buffConn),
	}
}

func (io *connman) Open(host string, port int) (fd int, err error) {
	io.lock.Lock()
	defer io.lock.Unlock()

	c, err := net.Dial("tcp4", fmt.Sprintf("%s:%d", host, port))
	if err != nil {
		return -1, err
	}

	fd = io.lastConn + 1

	if len(io.freeNumber) > 0 {
		fd = io.freeNumber[0]
		io.freeNumber = io.freeNumber[1:]
	}

	io.connectionList[fd] = newBufferedConn(c)

	if fd > io.lastConn {
		io.lastConn = fd
	}

	return fd, nil
}

func (io *connman) OpenUDP(host string, port int) (fd int, err error) {
	io.lock.Lock()
	defer io.lock.Unlock()

	//ip := ResolveAddr(host)
	//
	//c, err := net.DialUDP("udp4", nil, &net.UDPAddr{
	//    IP: ip,
	//    Port: port,
	//})
	// TODO: BROKEN
	c, err := net.Dial("udp4", fmt.Sprintf("%s:%d", host, port))

	if err != nil {
		return -1, err
	}

	fd = io.lastConn + 1

	if len(io.freeNumber) > 0 {
		fd = io.freeNumber[0]
		io.freeNumber = io.freeNumber[1:]
	}

	io.connectionList[fd] = newBufferedConn(c)

	if fd > io.lastConn {
		io.lastConn = fd
	}

	return fd, nil
}

func (io *connman) SetTimeout(fd int, millis uint64) error {
	io.lock.Lock()
	defer io.lock.Unlock()
	if c, ok := io.connectionList[fd]; ok {
		c.SetTimeout(millis)
		return nil
	}

	return fmt.Errorf("no such connection %d", fd)
}

func (io *connman) Peek(fd, n int) ([]byte, error) {
	io.lock.Lock()
	defer io.lock.Unlock()
	if c, ok := io.connectionList[fd]; ok {
		return c.Peek(n)
	}

	return nil, fmt.Errorf("no such connection %d", fd)
}

func (io *connman) Available(fd int) (n int, err error) {
	io.lock.Lock()
	defer io.lock.Unlock()
	if c, ok := io.connectionList[fd]; ok {
		return c.Available(), nil
	}

	return 0, fmt.Errorf("no such connection %d", fd)
}

func (io *connman) Write(fd int, data []byte) (n int, err error) {
	io.lock.Lock()
	defer io.lock.Unlock()
	if c, ok := io.connectionList[fd]; ok {
		return c.Write(data)
	}

	return 0, fmt.Errorf("no such connection %d", fd)
}

func (io *connman) Read(fd int, data []byte) (n int, err error) {
	io.lock.Lock()
	defer io.lock.Unlock()
	if c, ok := io.connectionList[fd]; ok {
		return c.Read(data)
	}

	return 0, fmt.Errorf("no such connection %d", fd)
}

func (io *connman) ReadPacket(fd int) ([]byte, *net.UDPAddr, error) {
	io.lock.Lock()
	defer io.lock.Unlock()
	if c, ok := io.connectionList[fd]; ok {
		return c.ReadPacket()
	}

	return nil, nil, fmt.Errorf("no such connection %d", fd)
}

func (io *connman) WriteTo(fd int, host string, port int, data []byte) (int, error) {
	io.lock.Lock()
	defer io.lock.Unlock()
	if c, ok := io.connectionList[fd]; ok {
		return c.WriteTo(host, port, data)
	}

	return 0, fmt.Errorf("no such connection %d", fd)
}

func (io *connman) Close(fd int) error {
	io.lock.Lock()
	defer io.lock.Unlock()
	if c, ok := io.connectionList[fd]; ok {
		err := c.Close()
		delete(io.connectionList, fd)
		io.freeNumber = append(io.freeNumber, fd)
		return err
	}
	return fmt.Errorf("no such connection %d", fd)
}
