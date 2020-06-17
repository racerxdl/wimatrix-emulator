#ifndef WIFI_H
#define WIFI_H

#include <compat/ipaddress.h>
#include <cstdint>

#define WL_CONNECTED 1

class EmulatedWiFi {

public:
  int begin(const char* ssid, const char *passphrase = NULL, int32_t channel = 0, const uint8_t* bssid = NULL, bool connect = true);
  int begin();

  IPAddress localIP();

  static int status();

  const char *getHostname() { return "EMULATOR"; }
  const char *macAddress() { return "00:00:00:00:00:00"; }
  String SSID() { return "DUMMY"; }
  int RSSI() { return -50; }
  IPAddress gatewayIP() { return IPAddress("10.0.0.1"); }
  IPAddress subnetMask() { return IPAddress("255.255.255.0"); }
};

#include <WiFiClient.h>

extern EmulatedWiFi WiFi;

#endif