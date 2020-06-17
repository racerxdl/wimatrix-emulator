#include <compat/ipaddress.h>
#include <iostream>
#include <sstream>

IPAddress::IPAddress(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
  this->address.bytes[0] = b0;
  this->address.bytes[1] = b1;
  this->address.bytes[2] = b2;
  this->address.bytes[3] = b3;
}

IPAddress::IPAddress(uint32_t address) {
  this->address.dword = address;
}

IPAddress::IPAddress(const uint8_t *address) {
  this->address.bytes[0] = address[0];
  this->address.bytes[1] = address[1];
  this->address.bytes[2] = address[2];
  this->address.bytes[3] = address[3];
}

IPAddress::IPAddress(const char *address) {
  fromString(address);
}

bool IPAddress::fromString(const char *address) {
  // 255.255.255.0
  std::string ip = address;
  std::stringstream s(ip);

  int a,b,c,d; //to store the 4 ints
  char ch; //to temporarily store the '.'
  s >> a >> ch >> b >> ch >> c >> ch >> d;

  if (a > 255 || a < 0 ||
      b > 255 || b < 0 ||
      c > 255 || c < 0 ||
      d > 255 || d < 0) {
    return false;
  }

  this->address.bytes[0] = (uint8_t)a;
  this->address.bytes[1] = (uint8_t)b;
  this->address.bytes[2] = (uint8_t)c;
  this->address.bytes[3] = (uint8_t)d;

  return true;
}

IPAddress& IPAddress::operator=(uint32_t address) {
  this->address.dword = address;
  return *this;
}

String IPAddress::toString() const {
  String output;

  output += String((int)this->address.bytes[0]);
  output += ".";
  output += String((int)this->address.bytes[1]);
  output += ".";
  output += String((int)this->address.bytes[2]);
  output += ".";
  output += String((int)this->address.bytes[3]);

  return output;
}