#include <WiFiUDP.h>
#include <serial.h>

WiFiUDP::WiFiUDP() {
  server_port = 0;
  remote_port = 0;
  tx_buffer_len = 0;
  rx_buffer_pos = 0;
  rx_buffer_len = 0;
  fd = -1;
}

uint8_t WiFiUDP::begin(IPAddress ip, uint16_t port) {
  this->fd = extconnopenudp(ip.toString().c_str(), int(port));

  return this->fd > -1 ? 1 : 0;
}


uint8_t WiFiUDP::begin(uint16_t port) {
  return begin(IPAddress(), port);
}

uint8_t WiFiUDP::beginMulticast(IPAddress a, uint16_t p) {
  // TODO
  Serial.println("WiFiUDP::beginMulticast NOT IMPLEMENTED");
  return -1;
}

void WiFiUDP::stop() {
  tx_buffer_len = 0;
  rx_buffer_len = 0;

  if (this->fd != -1) {
    extconnclose(this->fd);
    this->fd = -1;
  }
}

int WiFiUDP::beginMulticastPacket() {
  // TODO
  Serial.println("WiFiUDP::beginMulticastPacket NOT IMPLEMENTED");
  return -1;
}

int WiFiUDP::beginPacket() {
  if(!remote_port || this->fd == -1) {
    return 0;
  }

  tx_buffer_len = 0;

  return 1;
}

int WiFiUDP::beginPacket(IPAddress ip, uint16_t port) {
  return beginPacket(ip.toString().c_str(), port);
}

int WiFiUDP::beginPacket(const char *host, uint16_t port) {
  strncpy(remote_host, host, HOST_LEN);
  remote_port = port;

  return beginPacket();
}

int WiFiUDP::endPacket() {
  int sent = extconnwriteto(fd, tx_buffer, tx_buffer_len, remote_host, remote_port);

  if (sent < 0){
    return 0;
  }

  return 1;
}

size_t WiFiUDP::write(uint8_t c) {
  if(tx_buffer_len == PACKET_LEN){
    endPacket();
    tx_buffer_len = 0;
  }
  tx_buffer[tx_buffer_len++] = c;
  return 1;
}

size_t WiFiUDP::write(const uint8_t *buffer, size_t size) {
  for (size_t i=0;i<size;i++) {
    write(buffer[i]);
  }

  return size;
}

int WiFiUDP::parsePacket() {
  int port = 0;
  rx_buffer_len = extconnreadpacket (fd, rx_buffer, PACKET_LEN, remote_host, HOST_LEN, &port);
  remote_port = (uint16_t) port;
  return rx_buffer_len;
}

int WiFiUDP::available() {
  if (!rx_buffer_len) {
    return 0;
  }

  return rx_buffer_len - rx_buffer_pos > 0;
}

int WiFiUDP::read() {
  if (!rx_buffer_len) {
    return -1;
  }

  if (rx_buffer_pos >= rx_buffer_len) {
    rx_buffer_pos = 0;
    rx_buffer_len = 0;
    return -1;
  }

  return rx_buffer[rx_buffer_pos++];
}

int WiFiUDP::read(unsigned char* buffer, size_t len) {
  return read((char *)buffer, len);
}

int WiFiUDP::read(char* buffer, size_t len) {
  size_t c = 0;
  while (c < len) {
    int val = read();
    if (val == -1) {
      break;
    }
    buffer[c] = (char) val;
    c++;
  }

  return c;
}

int WiFiUDP::peek() {
  if (!rx_buffer_len || (rx_buffer_pos >= rx_buffer_len)) {
    return -1;
  }

  return rx_buffer[rx_buffer_pos];
}

void WiFiUDP::flush() {
  rx_buffer_pos = 0;
  rx_buffer_len = 0;
}

IPAddress WiFiUDP::remoteIP() {
  IPAddress ip;
  ip.fromString(remote_host);
  return ip;
}

uint16_t WiFiUDP::remotePort() {
  return (uint16_t)remote_port;
}

