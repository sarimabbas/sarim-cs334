# simulates and forwards keypresses to Godot

import serial
import time
import pyautogui

PORT = "/dev/cu.SLAB_USBtoUART"
BAUDRATE = 9600

ser = serial.Serial(port=PORT, baudrate=BAUDRATE)
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


def parseSerial(val_binary):
    # convert val to string
    val_string = val_binary.decode("utf-8")
    print(val_string)
    if "momentary" in val_string:
        return "momentary"


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
