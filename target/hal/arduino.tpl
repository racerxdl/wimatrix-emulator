#include <arduino.h>
#include <serial.h>
#include <backtrace.h>


void __attribute__((constructor)) initialize(void) {
  // Register Backtrace to print stacktrace on segfault
  //initBT();
}

