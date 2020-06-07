#include <iostream>

#ifndef SERIAL_H
#define SERIAL_H

class EmulatedSerial {

public:
  void begin(unsigned long baud) {
    std::cout << "[HAL] Serial.begin(" << baud << ")" << std::endl;
  }

  void println(std::string str) {
    std::cout << "[SERIAL] " << str << std::endl;
  }

};

extern EmulatedSerial Serial;

#endif