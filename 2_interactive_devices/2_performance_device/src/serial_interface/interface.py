# simulates and forwards keypresses to Godot

import serial
import time

import pyautogui
from pynput.keyboard import Key, Controller


PORT = "/dev/cu.SLAB_USBtoUART"
BAUDRATE = 9600

keyboard = Controller()

ser = serial.Serial(port=PORT, baudrate=BAUDRATE)
print(ser.name)


def loop():
    while True:
        parsed = ""
        get_val = ser.readline()
        parsed = get_val.decode("utf-8")
        print(parsed)

        handleJoystick(parsed)

        # keyboard.release("d")
        # if "momentary" in parsed:
        #     sendJump()
        # elif "joyLeft" in parsed:
        #     sendLeft()
        # elif "joyRight" in parsed:
        #     sendRight()
        # elif "switch" in parsed:
        #     sendSwitchCharacter()
        # time.sleep(0.01)


def handleJoystick(parsed):
    while "joyRight" in parsed:
        keyboard.press("d")
    keyboard.release()


def sendLeft():
    pyautogui.press("a")


def sendRight():
    pyautogui.press("d")


def sendJump():
    pyautogui.keyDown("w")
    time.sleep(0.02)
    pyautogui.keyUp("w")


def sendSwitchCharacter():
    pyautogui.keyDown("s")
    time.sleep(0.02)
    pyautogui.keyUp("s")


if __name__ == "__main__":
    loop()
