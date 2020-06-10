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
long micros();

#define OUTPUT 1
#define INPUT  0
#define HIGH   1
#define LOW    0

#define F_CPU 240000000
#define byte uint8_t

#define digitalPinToBitMask(P) ( 0 )
#define digitalPinToPort(P) ( 0 )
#define portOutputRegister(P) ( 0 )
#define portInputRegister(P) ( 0 )

void pinMode(int, int);

void yield();

#endif


#include <ardext.h>
#include <serial.h>