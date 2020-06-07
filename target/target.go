package target

/*

#cgo LDFLAGS: -ldl

#define _GNU_SOURCE
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <dlfcn.h>


void *handle;

static void *(*loop)() = NULL;
static void *(*setup)() = NULL;

int loadLibrary(const char *libname) {
    printf("LOADING %s\n", libname);
    handle = dlopen(libname, RTLD_LAZY | RTLD_GLOBAL);
    if (handle == NULL) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    loop = dlsym(handle, "loop");
    setup = dlsym(handle, "setup");

    return 0;
}

void arduLoop() {
    if (loop != NULL) {
        loop();
    }
}

void arduSetup() {
    if (setup != NULL) {
        setup();
    }
}
*/
import "C"
import (
	"fmt"
	"unsafe"
)

func Load(libname string) error {
	clibname := C.CString(libname)

	defer C.free(unsafe.Pointer(clibname))

	result := int(C.loadLibrary(clibname))

	if result != 0 {
		return fmt.Errorf("received error code %d", result)
	}

	return nil
}

func Loop() {
	C.arduLoop()
}

func Setup() {
	C.arduSetup()
}
