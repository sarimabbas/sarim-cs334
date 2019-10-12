#include <AxisJoystick.h>
#include <JC_Button.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// pin stuff
#define MOMENTARY_PIN 5
#define POLE_PIN 17
#define JOY_PIN 32

// WiFi stuff
#define CONSOLE_IP "192.168.1.2"
#define CONSOLE_PORT 57222
const char* ssid = "esp32";
const char* password = "12345678";
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);
WiFiUDP udp;

// hardware stuff
Button momentaryBtn(MOMENTARY_PIN);
AxisJoystick jstick(-1, -1, JOY_PIN);
int poleSwitchPrev = 0;
int poleSwitch = 0;

void readToggle() {
    int getVal = digitalRead(POLE_PIN);
    delay(50);
    if (digitalRead(POLE_PIN) == getVal) {
        poleSwitch = getVal;
    }
}

void sendPacket(String msg) {
    udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
    udp.printf(msg.c_str());
    udp.endPacket();
}

void setup() {
    // comms stuff
    // Serial.begin(9600);
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    server.begin();

    // hardware stuff
    momentaryBtn.begin();
    jstick.calibrate(0, 4095);
    pinMode(POLE_PIN, INPUT_PULLUP);
}

void loop() {
    // read inputs
    momentaryBtn.read();
    jstick.multipleRead();
    poleSwitchPrev = poleSwitch;
    readToggle();

    if (momentaryBtn.wasPressed()) {
        // Serial.println("momentary");
        sendPacket("momentary");
    }

    if (poleSwitch != poleSwitchPrev) {
        // Serial.println("switch");
        sendPacket("switch");
    }

    if (jstick.isUp()) {
        // Serial.println("joyLeft");
        sendPacket("joyLeft");
    } else if (jstick.isDown()) {
        // Serial.println("joyRight");
        sendPacket("joyRight");
    } else {
        // Serial.println("joyNone");
        sendPacket("joyNone");
    }
}
