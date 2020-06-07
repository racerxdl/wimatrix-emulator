#ifndef EEPROM_H
#define EEPROM_H

#include <iostream>
#include <sstream>
#include <ardext.h>

class EmulatedEEPROM {
private:
  uint16_t l;
public:
    void begin(unsigned long length) {
      std::stringstream ss;
      ss << "[HAL] EEPROM.begin(" << length << ")" << std::endl;
      std::string v = ss.str();
      extprint(v.c_str());
      this->l = (uint16_t)length;
    }

    void commit() {
      std::stringstream ss;
      ss << "[HAL] EEPROM.commit()" << std::endl;
      std::string v = ss.str();
      extprint(v.c_str());
    }

    uint8_t operator[](const int idx)  { return (uint8_t) extreadeeprom(idx); }
    uint8_t read(int idx)              { return (uint8_t) extreadeeprom(idx); }
    void write (int idx, uint8_t val)  { extseteeprom(idx, (char)val); }
    void update(int idx, uint8_t val)  { extseteeprom(idx, (char)val); }
    uint16_t length()                  { return this->l; }

    template< typename T > T &get( int idx, T &t ){
        uint8_t *ptr = (uint8_t*) &t;
        const int length = sizeof(T);
        for (int i = 0; i < length; i++) {
          ptr[i] = (uint8_t)read(idx + i);
        }
        return t;
    }

    template< typename T > const T &put( int idx, const T &t ){
        const uint8_t *ptr = (const uint8_t*) &t;
        const int length = sizeof(T);
        for (int i = 0; i < length; i++) {
          this->write(idx + i, ptr[i]);
        }
        return t;
    }
};

extern EmulatedEEPROM EEPROM;
#endif