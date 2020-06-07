package target

import "C"
import "fmt"

var redirectOut func(data string)

var eeprom = make([]uint8, 16*1024*1024)

//export goprintstring
func goprintstring(str *C.char) {
	gostr := C.GoString(str)

	if redirectOut != nil {
		redirectOut(gostr)
	} else {
		fmt.Printf(gostr)
	}
}

//export seteepromdata
func seteepromdata(addr C.int, val C.char) {
	goaddr := int(addr)
	goval := uint8(val)

	if len(eeprom) > goaddr {
		eeprom[goaddr] = goval
	}
}

//export geteepromdata
func geteepromdata(addr C.int) C.char {
	goaddr := int(addr)
	val := uint8(0)

	if len(eeprom) > goaddr {
		val = eeprom[goaddr]
	}

	return C.char(val)
}

// SetRedirectOut sets the stdout handle function
func SetRedirectOut(redir func(string)) {
	redirectOut = redir
}
