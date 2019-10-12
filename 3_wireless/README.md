# Going Wireless

> Module 3

## Table of contents

- [Going Wireless](#going-wireless)
  - [Table of contents](#table-of-contents)
  - [Implementation](#implementation)
    - [Controller](#controller)
    - [Art installation](#art-installation)

## Implementation

### Controller

The project utilizes some of the prior work done in Module 2. In particular it reuses the game-controller, with notable changes:

- The communication between the controller and the Pi is over WiFi, not over serial cable
  - This was suprisingly simple to change, because of the inherent modularity of the system and existing code
- The controller is battery powered
- The controller has two additional sensors

These changes make the controller a more robust, flexible, general-purpose input device.

### Art installation

The assignment called for a breaking of the traditional 1:1 link between the viewer and the art. Instead of developing my game (with a controller, the link is obvious), I decided to revisit the Becton cafe, and create installation art.

- The ultrasonic sensor on the controller is programmed to make its LEDs flash when a visitor gets near. This serves as a call to action
- 