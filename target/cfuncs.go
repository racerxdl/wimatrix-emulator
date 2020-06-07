package target

import "C"
import "fmt"

var redirectOut func(data string)

//export goprintstring
func goprintstring(str *C.char) {
	gostr := C.GoString(str)
	if redirectOut != nil {
		redirectOut(gostr)
	} else {
		fmt.Printf(gostr)
	}
}

// SetRedirectOut sets the stdout handle function
func SetRedirectOut(redir func(string)) {
	redirectOut = redir
}
