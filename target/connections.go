package target

import "C"
import (
	"fmt"
	"github.com/racerxdl/wimatrix-emulator/emulator/connman"
	"unsafe"
)

var connmanager connman.Manager

func init() {
	connmanager = connman.MakeManager()
}

//export connclose
func connclose(fd C.int) C.int {
	gofd := int(fd)

	err := connmanager.Close(gofd)
	if err != nil {
		fmt.Printf("Error closing fd %d: %s\n", gofd, err)
		return C.int(-1)
	}

	return C.int(0)
}

//export connopen
func connopen(host *C.char, port C.int) C.int {
	goport := int(port)
	gohost := C.GoString(host)

	fd, err := connmanager.Open(gohost, goport)
	if err != nil {
		fmt.Printf("Error opening connection to %s:%d: %s\n", gohost, goport, err)
		return C.int(-1)
	}

	return C.int(fd)
}

//export connwrite
func connwrite(fd C.int, buf *C.char, count C.int) C.int {
	gofd := int(fd)
	godata := C.GoBytes(unsafe.Pointer(buf), count)
	n, err := connmanager.Write(gofd, godata)
	if err != nil {
		fmt.Printf("Error writing to connection %d: %s\n", gofd, err)
		return 0
	}

	return C.int(n)
}

//export connread
func connread(fd C.int, buf *C.char, count C.int) C.int {
	gofd := int(fd)
	godata := (*[1 << 30]byte)(unsafe.Pointer(buf))[:count:count]
	n, err := connmanager.Read(gofd, godata)
	if err != nil {
		fmt.Printf("Error readiing from connection %d: %s\n", gofd, err)
		return 0
	}

	return C.int(n)
}

//export connpeek
func connpeek(fd C.int) C.int {
	gofd := int(fd)
	v, err := connmanager.Peek(gofd, 1)
	if err != nil {
		fmt.Printf("Error peeking on connection %d: %s\n", gofd, err)
		return C.int(-1)
	}

	if len(v) == 0 {
		return C.int(-1)
	}

	return C.int(int(v[0]))
}

//export connavailable
func connavailable(fd C.int) C.int {
	gofd := int(fd)
	count, err := connmanager.Available(gofd)
	if err != nil {
		fmt.Printf("Error reading available on connection %d: %s\n", gofd, err)
		return -1
	}

	return C.int(count)
}

//export connsettimeout
func connsettimeout(fd C.int, millis C.ulong) C.int {
	gofd := int(fd)
	gomillis := uint64(millis)
	err := connmanager.SetTimeout(gofd, gomillis)
	if err != nil {
		fmt.Printf("Error setting connection timeout %d: %s\n", gofd, err)
		return C.int(0)
	}

	return C.int(1)
}

//export connopenudp
func connopenudp(host *C.char, port C.int) C.int {
	goport := int(port)
	gohost := C.GoString(host)

	fd, err := connmanager.OpenUDP(gohost, goport)
	if err != nil {
		fmt.Printf("Error opening connection to %s:%d: %s\n", gohost, goport, err)
		return C.int(-1)
	}

	return C.int(fd)
}

//export connreadpacket
func connreadpacket(fd C.int, buf *C.char, buflen C.int, rhost *C.char, rhostlen C.int, rport *C.int) C.int {
	gofd := int(fd)
	godata := (*[1 << 30]byte)(unsafe.Pointer(buf))[:buflen:buflen]

	gorhost := (*[1 << 30]byte)(unsafe.Pointer(rhost))[:rhostlen:rhostlen]
	gorport := (*[1]int)(unsafe.Pointer(rport))[:1:1]

	pkt, dst, err := connmanager.ReadPacket(gofd)
	if err != nil {
		//fmt.Printf("Error reading packet from connection %d: %s\n", gofd, err)
		return 0
	}

	copy(gorhost, dst.IP.String())
	gorport[0] = dst.Port

	copy(godata, pkt)

	n := len(pkt)
	if n > int(buflen) {
		n = int(buflen)
	}

	return C.int(n)
}

//export connwriteto
func connwriteto(fd C.int, buf *C.char, count C.int, host *C.char, port C.int) C.int {
	gofd := int(fd)
	godata := C.GoBytes(unsafe.Pointer(buf), count)
	gohost := C.GoString(host)
	goport := int(port)

	n, err := connmanager.WriteTo(gofd, gohost, goport, godata)
	if err != nil {
		//fmt.Printf("Error writing to (%s:%d) %d: %s\n", gohost, goport, gofd, err)
		return 0
	}

	return C.int(n)
}
