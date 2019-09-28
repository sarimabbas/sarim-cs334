# Performance Device

> Module 2, Task 2

## Table of contents

- [Performance Device](#performance-device)
  - [Table of contents](#table-of-contents)
  - [Task details](#task-details)
  - [Installation](#installation)
    - [Raspberry Pi](#raspberry-pi)
      - [Enable OpenGL support](#enable-opengl-support)
      - [Use the browser](#use-the-browser)
      - [Use the compiled binary (smoother experience)](#use-the-compiled-binary-smoother-experience)
      - [Use ESP32 with hardware controls](#use-esp32-with-hardware-controls)
    - [Other platforms (Windows, macOS)](#other-platforms-windows-macos)
  - [Gameplay guide](#gameplay-guide)
    - [Keyboard controls](#keyboard-controls)
    - [ESP32 hardware controls](#esp32-hardware-controls)
  - [Development process](#development-process)
    - [Ideation](#ideation)
    - [Implementation](#implementation)
      - [Choice of engine](#choice-of-engine)
      - [Communication between ESP32 and the game](#communication-between-esp32-and-the-game)
  - [Attribution](#attribution)

## Task details

**Objective:**

Create a performance device. Performable is broadly interpreted and may include devices such as digital instruments, or game consoles.

**Constraints:**

- Demonstrate three modes of operation
  - A mode is a system state that alters how an input action effects the output
- Utilize the hardware given out in class
  - Momentary button
  - Joystick
  - SPST switch

## Installation

### Raspberry Pi

#### Enable OpenGL support

For all installation methods, this is required.

1. Run `sudo raspi-config`
2. Advanced Settings > GL Driver > GL driver (Full KMS)

#### Use the browser

1. Navigate to the `2_interactive_devices/2_performance_device/dist/html5` directory in a Terminal and run `python3 -m http.server`
2. Use a WebAssembly supported browser to navigate to `0.0.0.0:8000/Platformer Game.html`
3. Use an attached keyboard to play

#### Use the compiled binary (smoother experience)

1. Navigate to `2_interactive_devices/2_performance_device/dist/linux_32`
2. Run `frt_095_311_pi2.bin --main-pack game.pck`
3. Use an attached keyboard to plays

> Step 2 cannot be run via SSH, since X11 is required. Use VNC or connect the Raspberry Pi to a monitor instead.

#### Use ESP32 with hardware controls

First, make sure the hardware is connected as follows:

Then:

1. Navigate to `2_interactive_devices/2_performance_device/src/serial_interface`
2. Install dependencies with `pip3 install -r requirements.txt` (virtual environment recommended)
3. Run `python3 interface.py`  

Leave the terminal running in the background and focus on the game window. The game will intercept the hardware input.

### Other platforms (Windows, macOS)

1. You can use the browser, following the same process as with the Raspberry Pi
2. Use an attached keyboard to play

## Gameplay guide

You are in control of a bunny. Hop across the platforms and try to reach the end of the level. Do not fall far or hit spikes.

### Keyboard controls

- `w` to jump
- `a` to move left
- `d` to move right
- `s` to switch character

### ESP32 hardware controls

- Move the joystick left or right to move in that direction
- Press the momentary button to jump
- Flip the pole switch to switch character

## Development process

### Ideation

I wanted to create a video game console. As a single person team, I wanted to create a game that would be of moderate complexity to create and that would run smoothly on the Pi.

With the limited controls available, I thought about which game formats would work the best. I shortlisted two concepts:

1. An endless runner (like Jetpack Joyride)
2. A platforming game (like Mario)

![Ideation](./docs/ideation.jpg)

Both ideas are not novel, but would let me explore the game engine (below) and are well suited to traditional hardware controls like joysticks. Any meaningful addition of complexity (for e.g. isometric terrain) would be too difficult to code up in Processing, so I had to think of alternate implementations.

In the end I opted for the platformer because it was easier to implement, given the time and resource constraints.

### Implementation

![Screenshot](./docs/screen.jpg)

#### Choice of engine

I considered a number of options:

- Processing: no physics or other nice features. Have to code all logic yourself
- Godot: popular engine but runs slowly on Raspberry Pi
- LOVE: runs well on the Pi and similar to Processing, but uses Lua, with which I'm unfamiliar

In the end I elected to use Godot, using an older renderer which has compatibility with most hardware.

I was really impressed by how many features Godot has out of the box, including:

- Physics, movement, collision
- Sprite animations
- Camera movements
- Animated parallax backgrounds

Creating even a simple platformer would have been a pain in Processing but was relatively simple in Godot.

I relied heavily on Godot's documentation and a Udemy course I've been meaning to complete since sophomore year.

#### Communication between ESP32 and the game

Godot has little support for WebSockets and Serial data input. I tried to figure out the best way to get data from the ESP32 to the game.

In the end, I had a setup like the diagram below:

- The ESP32 transmits input data over serial
- A Python helper program on the Pi transforms those inputs into simulated key presses
- The Godot game window remains in focus on the Pi, and receives the keypresses.

## Attribution

- Use of Godot documentation and Udemy course
- Sound effects from OpenGameArt.org
  - Spell by Bart Kelsey
  - Chiptune Adventures by SubspaceAudio
- Sprites from Kenney.nl

