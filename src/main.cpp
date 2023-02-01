#include <Arduino.h>
#include <ArduinoJson.h>
#include <WakeOnLan.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP UDP;
WakeOnLan WOL(UDP);

const char *SSID = "your_wifi_ssid";
const char *PWD = "your_wifi_password";

WebServer server(80);

StaticJsonDocument<250> jsonDocument;

void wakePC() {
  // PC MAC address to wake
  const char *MACAddress = "XX:XX:XX:XX:XX:XX";

  WOL.sendMagicPacket(MACAddress);
}

void handlePost() {
  if (server.hasArg("plain") == false) {
  }
  String body = server.arg("plain");
  deserializeJson(jsonDocument, body);

  int wake_value = jsonDocument["wake"];
  if (wake_value == 1) {
    wakePC();
  }
  server.send(200, "application/json", "{}");
}

void setup_routing() {
  server.on("/wake", HTTP_POST, handlePost);

  server.begin();
}

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(SSID, PWD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());

  setup_routing();
}

void loop() { server.handleClient(); }