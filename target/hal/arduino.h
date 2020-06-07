#ifndef ARDUINO_H
#define ARDUINO_H

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

#endif