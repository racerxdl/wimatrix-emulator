#include <WiFi.h>
#include <WiFiUDP.h>
#include <NTPClient.h>

const char* ssid     = "ELTNMob";
const char* password = "pzxz7649";

WiFiUDP ntpUDP;

int16_t utc = -3; //UTC -3:00 Brazil
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", utc*3600, 60000);

int getHours() {
  return timeClient.getHours();
}

int getMinutes() {
  return timeClient.getMinutes();
}

int getSeconds() {
  return timeClient.getSeconds();
}

void setup() {
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    // NTP
    timeClient.begin();
    timeClient.update();
}

void loop() {
  timeClient.update();
  Serial.print("Hour: ");
  Serial.print(getHours());
  Serial.print(" Minutes: ");
  Serial.print(getMinutes());
  Serial.print(" Seconds: ");
  Serial.println(getSeconds());
  delay(1000);
}
