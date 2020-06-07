#include <iostream>

#ifndef SERIAL_H
#define SERIAL_H

class EmulatedSerial {

public:
  void begin(unsigned long baud) {
    std::cout << "Serial.begin(" << baud << ")" << std::endl;
  }

  void println(std::string str) {
    std::cout << str << std::endl;
  }

};

extern EmulatedSerial Serial;

#endif