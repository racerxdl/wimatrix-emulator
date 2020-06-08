#ifndef WIFICLIENT_H
#define WIFICLIENT_H

#include <compat/ipaddress.h>

class WiFiClient {
private:
  int fd;

public:
  WiFiClient() : fd(-1) {}
  WiFiClient(int fd) : fd(1) {}
  int connect(IPAddress ip, uint16_t port);
  int connect(IPAddress ip, uint16_t port, int32_t timeout);
  int connect(const char *host, uint16_t port);
  int connect(const char *host, uint16_t port, int32_t timeout);
  size_t write(uint8_t data);
  size_t write(const uint8_t *buf, size_t size);
  int available();
  int read();
  int read(uint8_t *buf, size_t size);
  int peek();
  void flush();
  void stop();
  uint8_t connected();

  int print(const String &str);
  String readStringUntil(const char terminator);
};

#endif