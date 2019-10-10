#include <OSCMessage.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>

/* Put your SSID & Password */
const char* ssid = "cynthiaesp32";  // Enter SSID here
const char* password = "12345678";  // Enter Password here

/* Put IP Address details */
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

WiFiUDP udp;

void setup() {
    Serial.begin(115200);

    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);

    server.begin();
}

void loop() {
    udp.beginPacket("192.168.1.2", 57222);
    udp.printf("elllo");
    udp.endPacket();

    // Wait for 1 second
    delay(1000);
}
