#!/usr/bin/env python3
# simulates and forwards keypresses to Godot

import serial
import time
import pyautogui

ser = serial.Serial(port="/dev/cu.usbmodem14101", baudrate=9600)
print(ser.name)


def loop():
    while True:
        get_val = ser.readline()
        parsed = parseSerial(get_val)
        if parsed == "momentary":
            sendJump()
        elif parsed == "joyLeft":
            sendLeft()
        elif parsed == "joyRight":
            sendRight()
        elif parsed == "switch":
            sendSwitchCharacter()
        time.sleep(0.1)


def parseSerial():
    pass


def sendJump():
    keyPress("w")


def sendLeft():
    keyPress("a")


def sendRight():
    keyPress("d")


def sendSwitchCharacter():
    keyPress("s")


def keyPress(key):
    pyautogui.keyDown(key)
    time.sleep(0.02)
    pyautogui.keyUp(key)


if __name__ == "__main__":
    loop()
