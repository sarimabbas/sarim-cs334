# Musical Instrument

> CPSC 334 - Creative Embedded Systems - Module 7 - Final Project

## Table of Contents

- [Musical Instrument](#musical-instrument)
  - [Table of Contents](#table-of-contents)
  - [Technical Challenges](#technical-challenges)
    - [HC-SR04 readings](#hc-sr04-readings)

## Technical Challenges

### HC-SR04 readings

Having used the sensor in a previous project, the readings can be quite volatile and noisy. For the instrument, much smoother transitions are required. One suggestion was to drive smoother *changes* to a distance measure rather than updating absolute distance. Another was to take multiple readings, discard outliers and take the average. 

Eventually, I found a library called NewPing that does a median computation automatically. Moreover, it can work with a single pin input from the sensor, which works well, since the instrument makes use of many such sensors. 
