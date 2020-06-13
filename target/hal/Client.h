#pragma once

#include <compat/ipaddress.h>

class Client {

public:
  virtual int connect(IPAddress ip, uint16_t port) = 0;
  virtual int connect(const char *host, uint16_t port) = 0;
  virtual size_t write(uint8_t) = 0;
  virtual size_t write(const uint8_t *buf, size_t size) = 0;
  virtual int available() = 0;
  virtual int read() = 0;
  virtual int read(uint8_t *buf, size_t size) = 0;
  virtual int peek() = 0;
  virtual void flush() = 0;
  virtual void stop() = 0;
  virtual uint8_t connected() = 0;
  virtual operator bool() = 0;
  virtual void setTimeout(unsigned long timeout) = 0;
  virtual size_t readBytes( char *buffer, size_t length) = 0;

  size_t readBytes( uint8_t *buffer, size_t length) { return this->readBytes((char *)buffer, length); }
};
