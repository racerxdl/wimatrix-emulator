package target

/*

#cgo LDFLAGS: -ldl

#define _GNU_SOURCE
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <dlfcn.h>

// Golang Functions
extern void 			goprintstring(char *str);
extern void 			seteepromdata(int addr, char val);
extern char 			geteepromdata(int addr);
extern void 			goprintstring(char *str);
extern int  			connclose    (int fd);
extern int  			connopen     (char *host, int port);
extern unsigned long  	connwrite    (int fd, char *buf, unsigned long count);
extern unsigned long    connread     (int fd, char *buf, unsigned long count);
extern unsigned long    connpeek     (int fd);
extern int              connavailable(int fd);

// Loaded code functions
#define FN_PRINT          0
#define FN_SET_EEPROM     1
#define FN_GET_EEPROM     2
#define FN_CONN_CLOSE     3
#define FN_CONN_OPEN      4
#define FN_CONN_WRITE     5
#define FN_CONN_READ      6
#define FN_CONN_PEEK      7
#define FN_CONN_AVAILABLE 8

static void *handle;
static void (*loop)() = NULL;
static void (*setup)() = NULL;
static void (*setFunction)(int functionId, void *func) = NULL;

int loadLibrary(const char *libname) {
    handle = dlopen(libname, RTLD_LAZY | RTLD_GLOBAL);
    if (handle == NULL) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    loop = dlsym(handle, "loop");
    setup = dlsym(handle, "setup");
    setFunction = dlsym(handle, "setFunction");

    if (setFunction != NULL) {
    	setFunction(FN_PRINT, 			goprintstring);
    	setFunction(FN_SET_EEPROM, 		seteepromdata);
    	setFunction(FN_GET_EEPROM, 		geteepromdata);
    	setFunction(FN_CONN_CLOSE, 		connclose);
    	setFunction(FN_CONN_OPEN, 		connopen);
    	setFunction(FN_CONN_WRITE, 		connwrite);
    	setFunction(FN_CONN_READ, 		connread);
    	setFunction(FN_CONN_PEEK, 		connpeek);
    	setFunction(FN_CONN_AVAILABLE, 	connavailable);
    }

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
