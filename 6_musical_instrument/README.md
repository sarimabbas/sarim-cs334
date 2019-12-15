# Musical Instrument

> CPSC 334 - Creative Embedded Systems - Module 7 - Final Project

## Introduction

The laser piano can be played by moving one’s fingers through the air. It is motivated by the desire to break the tactile link between the musician and their instrument, and to create opportunities for learning and experimentation. The enclosure is made of laser cut pieces of acrylic to give transparency into the underlying electronics. Thirteen laser diodes shine beams onto corresponding photoresistors: these beams correspond to the keys in a traditional piano octave. Each laser beam can be “plucked” by a finger to play a note. The beams can optionally be visualized using mist. A dial allows one to switch octaves. At the heart of the system is an ESP32 module that relays sensor data,  using the MIDI protocol, to a laptop running any compatible DAW software e.g. Logic.

## Table of Contents

- [Musical Instrument](#musical-instrument)
  - [Introduction](#introduction)
  - [Table of Contents](#table-of-contents)
  - [Budget](#budget)
  - [Technical Challenges](#technical-challenges)
    - [HC-SR04 readings](#hc-sr04-readings)
    - [Photosensor readings](#photosensor-readings)
    - [MIDI setup](#midi-setup)
    - [ESP32 issues](#esp32-issues)
  - [Enclosure design](#enclosure-design)
    - [Use of display and rotary encoder](#use-of-display-and-rotary-encoder)

## Budget

| Name                  | Units | \$/unit      | Total \$ cost |
| --------------------- | ----- | ------------ | ------------- |
| Wooden dowels         | 2     | Free in CEID | 0             |
| 13 x 11 acrylic piece | 1     | Free in CEID | 0             |
| Laser diodes          | 13    | 0.55         | 7.15          |
| Photoresistors        | 13    | Free in CEID | 0             |
| DAW e.g. Logic        | 1     | Variable     | -             |

Tools required:

- Laser cutter
- Drill
- Hot glue
- Wire cutter
- Soldering iron

## Technical Challenges

### HC-SR04 readings

Having used the sensor in a previous project, the readings can be quite volatile and noisy. For the instrument, much smoother transitions are required. One suggestion was to drive smoother _changes_ to a distance measure rather than updating absolute distance. Another was to take multiple readings, discard outliers and take the average.

Eventually, I found a library called NewPing that does a median computation automatically. Moreover, it can work with a single pin input from the sensor, which works well, since the instrument makes use of many such sensors.

### Photosensor readings

Analog: range from 150- for dark to 500 for ambient to 1500+ for bright, directed light.

### MIDI setup

![MIDI setup](./docs/midi_setup.png)

Many options were tried:

- ESP32 MIDI BLE => MIDI in to Logic on macOS
- ESP32 Serial Out => Python Script on macOS => MIDI in to Logic on macOS
- ESP32 MIDI over Serial Out => Hairless MIDI app on macOS => MIDI in to Logic on macOS

The first option was not reliable as the Bluetooth connection between the ESP32 and macOS kept dropping.

The second and third options are quite similar, but whereas I would have had to write the logic by myself in Python using a library like [Mido](https://mido.readthedocs.io/en/latest/), with Hairless MIDI this is already taken care of.

Hairless MIDI is currently compiled for 32-bit, which posed a problem since I am using macOS Catalina. However, [this GitHub issue](https://github.com/projectgus/hairless-midiserial/issues/51) has an experimental 64-bit version. However, the Preferences must be re-saved in order for the program to work without crashing.

The Hairless MIDI website [describes the required setup](https://projectgus.github.io/hairless-midiserial/), which involves enabling an IAC Driver Bus in the macOS MIDI settings.

### ESP32 issues

- Some pins (e.g. GPIO 13) are used for boot up, and setting them as INPUT interferes with the flashing process. The solution is not to use the pin or leave it unplugged during boot. [Relevant issue on Github](https://github.com/espressif/esp-idf/issues/113).

## Enclosure design

Initially I had wanted to make the instrument a black-box, which would add to the mystery of the workings of the instrument. But after accidentally laser cutting a piece of acrylic instead of wood, I thought it would be interesting to pivot and give the user/viewer insight into the bare metal.

To effectively showcase the inner workings and electronics, I gave lots of thought to the circuit layout, its symmetry and color coding of wiring. The photoresistors, for example, are soldered to common rails to minimize clutter.

### Use of display and rotary encoder

To add the octave switching functionality, I paired a rotary encoder to act as a dial, with a display providing feedback. The display also provides feedback during the startup calibration sequence.

Surprisingly, the display does not require VCC and GND connections, and the data pin connections suffice.

Both components are mounted on independent breadboards to make the instrument modular.

The rotary encoder saturates at very low or high values, which allows the user to easily cycle through the octaves.

The encoder library used has an outdated version available in the Arduino Library manager, so I manually downloaded and included the master branch available at its GitHub page.
