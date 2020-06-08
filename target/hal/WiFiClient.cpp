#include <WiFiClient.h>
#include <ardext.h>

int WiFiClient::connect(IPAddress ip, uint16_t port) {
  String ipstr = ip.toString();
  this->fd = extconnopen(ipstr.c_str(), int(port));
  return this->fd > -1 ? 1 : 0;
}

int WiFiClient::connect(IPAddress ip, uint16_t port, int32_t timeout) {
  // TODO: Timeout
  return this->connect(ip, port);
}

int WiFiClient::connect(const char *host, uint16_t port) {
  this->fd = extconnopen(host, int(port));
  return this->fd > -1 ? 1 : 0;
}

int WiFiClient::connect(const char *host, uint16_t port, int32_t timeout) {
  // TODO: Timeout
  return this->connect(host, port);
}

size_t WiFiClient::write(uint8_t data) {
  uint8_t buf[1];
  buf[0] = data;
  return extconnwrite(this->fd, (const char *)buf, 1);
}

size_t WiFiClient::write(const uint8_t *buf, size_t size) {
  return extconnwrite(this->fd, (const char *)buf, size);
}

int WiFiClient::available() {
  return extconnavailable(this->fd);
}

int WiFiClient::read() {
  uint8_t buf[1];
  int n = extconnread(this->fd, (char *)buf, 1);

  if (n == 1) {
    return int(buf[0]);
  }

  return -1;
}

int WiFiClient::read(uint8_t *buf, size_t size) {
  return extconnread(this->fd, (char *)buf, size);
}

int WiFiClient::peek() {
  return extconnpeek(this->fd);
}

void WiFiClient::flush() {
  // Needed?
}

void WiFiClient::stop() {
  extconnclose(this->fd);
  this->fd = -1;
}

uint8_t WiFiClient::connected() {
  return this->fd > -1;
}

int WiFiClient::print(const String &str) {
  return this->write((const unsigned char *)str.c_str(), str.length());
}

String WiFiClient::readStringUntil(const char terminator) {
  String output;
  int c = 0;
  int availableBytes;

  while (c != (int)terminator) {
    // Wait for data available
    while (availableBytes < 1) {
      availableBytes = this->available();
      if (availableBytes == -1) {
        // ERROR
        break;
      }
    }

    if (availableBytes == -1) {
      // ERROR
      break;
    }

    c = this->read();
    if (c == -1) {
      // ERROR
      break;
    }
    output += (char)c;
  }

  return output;
}