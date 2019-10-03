#include <JC_Button.h>
#include <AxisJoystick.h>

#define MOMENTARY_PIN 5
#define POLE_PIN 17
#define JOY_VRX_PIN 32
#define JOY_VRY_PIN 33

Button momentaryBtn(MOMENTARY_PIN);
AxisJoystick jstick(-1, JOY_VRX_PIN, JOY_VRY_PIN);

int poleSwitchPrev = 0;
int poleSwitch = 0;

void readToggle()
{
    int getVal = digitalRead(POLE_PIN);
    delay(50);
    if (digitalRead(POLE_PIN) == getVal)
    {
        poleSwitch = getVal;
    }
}

void setup()
{
    // Set pin mode
    Serial.begin(9600);
    momentaryBtn.begin();
    jstick.calibrate(0, 4095);
    pinMode(POLE_PIN, INPUT_PULLUP);
}

void loop()
{
    // read inputs
    momentaryBtn.read();
    jstick.multipleRead();
    poleSwitchPrev = poleSwitch;
    readToggle();

    if (momentaryBtn.wasPressed())
    {
        Serial.println("momentary");
    }

    if (poleSwitch != poleSwitchPrev)
    {
        Serial.println("switch");
    }

    if (jstick.isLeft())
    {
        Serial.println("joyLeft");
    }
    else if (jstick.isRight())
    {
        Serial.println("joyRight");
    }
    else
    {
        // Serial.println("joyNone");
    }
}
