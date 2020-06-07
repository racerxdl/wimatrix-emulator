#include <iostream>
#include <sstream>
#include <ardext.h>
#include <compat/astring.h>

#ifndef SERIAL_H
#define SERIAL_H

class EmulatedSerial {

public:
  void begin(unsigned long baud) {
    std::stringstream ss;
    ss << "[HAL] Serial.begin(" << baud << ")" << std::endl;
    std::string v = ss.str();
    extprint(v.c_str());
  }

  void println(String str) {
    String linedString = str;
    linedString += "\n";
    extprint(linedString.c_str());
  }

  void print(String str) {
    extprint(str.c_str());
  }

};

extern EmulatedSerial Serial;

#endif