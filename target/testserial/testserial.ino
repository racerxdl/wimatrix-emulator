#include <EEPROM.h>

#define SSID_LENGTH 64
#define PASSWORD_LENGTH 32
#define HOSTNAME_LENGTH 16

struct Config {
  // WIFI
  char SSID[SSID_LENGTH];
  char WifiPassword[PASSWORD_LENGTH];
  char Hostname[HOSTNAME_LENGTH];
  char OTAPassword[PASSWORD_LENGTH];

  // MQTT
  char MQTTHostname[HOSTNAME_LENGTH];
  char MQTTUsername[PASSWORD_LENGTH];
  char MQTTPassword[PASSWORD_LENGTH];

} currentConfig;

const size_t ConfigLength = sizeof(currentConfig);

void Load() {
  char *c = (char *)(&currentConfig);
  for (int i=0; i<ConfigLength;i++) {
    c[i] = EEPROM.read(i);
  }

  // Pad all strings to be null terminated
  currentConfig.SSID[SSID_LENGTH-1] = 0x00;
  currentConfig.WifiPassword[PASSWORD_LENGTH-1] = 0x00;
  currentConfig.OTAPassword[PASSWORD_LENGTH-1] = 0x00;
  currentConfig.Hostname[HOSTNAME_LENGTH-1] = 0x00;
  currentConfig.MQTTHostname[HOSTNAME_LENGTH-1] = 0x00;
  currentConfig.MQTTUsername[PASSWORD_LENGTH-1] = 0x00;
  currentConfig.MQTTPassword[PASSWORD_LENGTH-1] = 0x00;
}

void Save() {
  currentConfig.SSID[SSID_LENGTH-1] = 0x00;
  currentConfig.WifiPassword[PASSWORD_LENGTH-1] = 0x00;
  currentConfig.OTAPassword[PASSWORD_LENGTH-1] = 0x00;
  currentConfig.Hostname[HOSTNAME_LENGTH-1] = 0x00;
  currentConfig.MQTTHostname[HOSTNAME_LENGTH-1] = 0x00;
  currentConfig.MQTTUsername[PASSWORD_LENGTH-1] = 0x00;
  currentConfig.MQTTPassword[PASSWORD_LENGTH-1] = 0x00;

  char *c = (char *)(&currentConfig);
  for (int i=0; i<ConfigLength;i++) {
    EEPROM.write(i, c[i]);
  }
  EEPROM.commit();
}

String GetMQTTHost() {
  return String(currentConfig.MQTTHostname);
}

void SaveMQTTHost(String hostname) {
    int maxLen = HOSTNAME_LENGTH-1;
    if (hostname.length() < maxLen) {
      maxLen = hostname.length();
    }
    for (int i = 0; i < HOSTNAME_LENGTH; i++) {
      if (i < maxLen) {
        currentConfig.MQTTHostname[i] = hostname[i];
      } else {
        currentConfig.MQTTHostname[i] = 0x00;
      }
    }
    Save();
}

void setup() {
  Serial.begin(115200);
  Serial.println("HELLO WORLD");
  EEPROM.begin(ConfigLength);
  Serial.print("MQTT Host: ");
  Serial.println(GetMQTTHost());
  SaveMQTTHost("HUEBR");
  Load();
  Serial.print("MQTT Host: ");
  Serial.println(GetMQTTHost());
  SaveMQTTHost("WOLOLO");
  Load();
  Serial.print("MQTT Host: ");
  Serial.println(GetMQTTHost());
}

void loop() {
  Serial.println("LIVE ON");
  delay(1000);
}