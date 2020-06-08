#include <compat/ipaddress.h>
#include <iostream>

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

bool IPAddress::fromString(const char *address) {
  // 255.255.255.0
  // TODO
  std::cerr << "NOT IMPLEMENTED" << std::endl;
  return false;
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