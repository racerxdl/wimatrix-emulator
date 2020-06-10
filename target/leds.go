package target

import "C"

var cbPutPixel func(pixel uint32)
var cbEndPanelUpdate func()

//export putpixel
func putpixel(pixel C.uint) {
	if cbPutPixel != nil {
		gopixel := uint32(pixel)
		cbPutPixel(gopixel)
	}
}

//export endpanelupdate
func endpanelupdate() {
	if cbEndPanelUpdate != nil {
		cbEndPanelUpdate()
	}
}

func SetPutPixel(fn func(pixel uint32)) {
	cbPutPixel = fn
}

func SetEndPanelUpdate(fn func()) {
	cbEndPanelUpdate = fn
}
