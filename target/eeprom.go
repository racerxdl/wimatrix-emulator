package target

import "C"

var eeprom = make([]uint8, 16*1024*1024)

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
