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

global_vars = {"prev_parsed": "", "parsed": ""}


def loop():
    while True:
        get_val = ser.readline()
        global_vars["prev_parsed"] = global_vars["parsed"]
        global_vars["parsed"] = get_val.decode("utf-8")
        handleJoystick()
        handleButtons()

        # keyboard.release("d")
        # if "momentary" in parsed:d
        #     sendJump()
        # elif "joyLeft" in parsed:
        #     sendLeft()
        # elif "joyRight" in parsed:
        #     sendRight()
        # elif "switch" in parsed:
        #     sendSwitchCharacter()


def handleJoystick():
    # if "joyRight" in global_vars["parsed"]:
    #     if not "joyRight" in global_vars["prev_parsed"]:
    #         keyboard.press("d")
    # else:
    #     keyboard.release("d")
    if (
        "joyRight" in global_vars["parsed"]
        and "joyRight" not in global_vars["prev_parsed"]
    ):
        keyboard.press("d")
    elif (
        "joyLeft" in global_vars["parsed"]
        and "joyLeft" not in global_vars["prev_parsed"]
    ):
        keyboard.press("a")

    if "joyNone" in global_vars["parsed"]:
        keyboard.release("a")
        keyboard.release("d")


def handleButtons():
    if "momentary" in global_vars["parsed"]:
        sendJump()


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
