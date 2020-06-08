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
static void *handle;
static void (*loop)() = NULL;
static void (*setup)() = NULL;
static void (*setprintfunction)(void (*printfn)(char *)) = NULL;
static void (*setSetEEPROMData)(void (*seteeprom)(int addr, char data)) = NULL;
static void (*setReadEEPROMData)(char (*readeeprom)(int addr)) = NULL;

int loadLibrary(const char *libname) {
    handle = dlopen(libname, RTLD_LAZY | RTLD_GLOBAL);
    if (handle == NULL) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    loop = dlsym(handle, "loop");
    setup = dlsym(handle, "setup");
    setprintfunction = dlsym(handle, "setprintfunction");
    setSetEEPROMData = dlsym(handle, "setSetEEPROMData");
    setReadEEPROMData = dlsym(handle, "setReadEEPROMData");

    if (setprintfunction != NULL) {
    	setprintfunction(goprintstring);
    }
    if (setSetEEPROMData != NULL) {
    	setSetEEPROMData(seteepromdata);
    }
    if (setReadEEPROMData != NULL) {
    	setReadEEPROMData(geteepromdata);
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
