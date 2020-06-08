#ifndef ARDUINO_H
#define ARDUINO_H

#include <string>
#include <compat/astring.h>

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif
void loop();
void setup();

#ifdef __cplusplus
}
#endif

void delay(unsigned long);
long millis();

#endif