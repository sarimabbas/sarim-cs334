# Going Wireless

> Module 3

![Preview](./docs/full.jpg)

## Table of contents

- [Going Wireless](#going-wireless)
  - [Table of contents](#table-of-contents)
  - [Overview](#overview)
  - [Vision](#vision)
  - [Video demo](#video-demo)
  - [Implementation](#implementation)
    - [Communication over WiFi](#communication-over-wifi)
    - [Enclosure](#enclosure)
    - [Battery power](#battery-power)
    - [Additional sensors](#additional-sensors)

## Overview

The project utilizes some of the prior work done in Module 2. In particular it reuses the game-controller, with notable changes:

- The communication between the controller and the Pi is over WiFi, not over serial cable
- The controller is battery powered and has a charging circuit
- The controller has two additional sensors
  - A DIY sensor
  - A photocell

These changes make the controller a more robust, flexible, general-purpose input device. 

## Vision

The assignment called for a breaking of the traditional 1:1 link between the viewer and the art. Instead of developing my game (with a controller, the link is obvious), I decided to revisit the Becton cafe, and create installation art.

- The ultrasonic sensor on the controller is programmed to make its LEDs flash when a visitor gets near. This serves as a call to action

## Video demo

It can be viewed here: <https://www.youtube.com/watch?v=0Xa9AYKj17s>

## Implementation

### Communication over WiFi

The previous version of the controller required a physical link to the console over USB serial in order to transmit sensor (e.g. joystick) data.

This version utilizes the ESP32 as a WiFi access-point. The console running the game (a Raspberry Pi or Laptop) can connect to the AP and receive sensor data over UDP. The data is interpreted by a modified Python interface (from  Module 2), and transformed into emulated keypresses.

Debugging over WiFi is not as easy as with serial. The console had trouble reconnecting to the AP after the ESP32 was reset, and several attempts were required to obtain an IP address.

Latency was suprisingly unnoticeable with the game, despite the wireless transmission. This held true even when using the controller multiple feet away.

### Enclosure

The 3D-printed case from the previous module was too small to hold additional components, so I built a more pragmatic, roomier enclosure from matboard.

![Corner](./docs/corner.jpg)

![Top](./docs/top.jpg)

### Battery power

A charging circuit was created by soldering the TP4056 charging board with a JST connector, which was connected to a LiPo battery. 

Battery power comes with its own complications:
- The thresholds for the DIY sensor needed to be tweaked, since the ESP32 touch pin read attenuated inputs. 

The LiPo battery discharges relatively quickly (especially given that the ESP32 is constantly streaming sensor data over WiFi), so I also soldered a power switch with an LED indicator to turn off the controller when not in use.

### Additional sensors

The DIY sensor is a capacitive touch sensor, acting as a momentary button. It is made from layers of aluminum foil wrapped around cardboard, and connected to one of the ESP32's touch pins.

![DIY sensor](./docs/diy.jpg)

A photocell is also present, and sends ambient light levels to the console. The purpose of the sensor is to link the player's physical environment with the game environment.
