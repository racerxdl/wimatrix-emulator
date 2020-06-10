#include <iostream>
#include <sstream>
#include <ardext.h>
#include <compat/astring.h>
#include <compat/stringable.h>

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

  void println(const String str) {
    String linedString = str;
    linedString += "\n";
    extprint(linedString.c_str());
  }

  void println(const Stringable &obj) {
    String linedString = obj.toString();
    linedString += "\n";
    extprint(linedString.c_str());
  }

  void println() {
    String linedString("\n");
    extprint(linedString.c_str());
  }

  void print(const String str) {
    extprint(str.c_str());
  }

  void print(const Stringable &obj) {
    extprint(obj.toString().c_str());
  }

  void print(const uint32_t val) {
    extprint(String(val).c_str());
  }

  void write(const Stringable &obj) {
    extprint(obj.toString().c_str());
  }

  void write(const uint8_t u) {
    String str;
    str += (char)u;
    extprint(str.c_str());
  }
};

extern EmulatedSerial Serial;

#endif