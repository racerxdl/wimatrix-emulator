#include <iostream>
#include <sstream>
#include <ardext.h>

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

  void println(std::string str) {
    std::stringstream ss;
    ss << str << std::endl;
    std::string v = ss.str();
    extprint(v.c_str());
  }

  void print(std::string str) {
    std::stringstream ss;
    ss << str;
    std::string v = ss.str();
    extprint(v.c_str());
  }

};

extern EmulatedSerial Serial;

#endif