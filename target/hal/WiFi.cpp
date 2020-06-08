#include <WiFi.h>
#include <serial.h>
#include <compat/astring.h>

EmulatedWiFi WiFi;

const IPAddress EmulatedIP(255, 255, 255, 254);

int EmulatedWiFi::begin(const char* ssid, const char *passphrase, int32_t channel, const uint8_t* bssid, bool connect) {
  std::stringstream ss;
  ss << "[HAL] WiFi.begin(" << ssid << ", " << passphrase << ")";
  Serial.println(ss.str());

  return 0;
}

int EmulatedWiFi::begin() {
  return this->begin("NULL", NULL, 0, NULL, true);
}

IPAddress EmulatedWiFi::localIP() {
  return EmulatedIP;
}

int EmulatedWiFi::status() {
  return WL_CONNECTED;
}