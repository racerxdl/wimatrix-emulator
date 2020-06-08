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
};

#include <WiFiClient.h>

extern EmulatedWiFi WiFi;

#endif