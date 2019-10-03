#include <JC_Button.h>
#include <AxisJoystick.h>

#define MOMENTARY_PIN 5
#define POLE_PIN 17
#define JOY_VRX_PIN 32
#define JOY_VRY_PIN 33

Button momentaryBtn(MOMENTARY_PIN);
// AxisJoystick jstick(-1, JOY_VRX_PIN, JOY_VRY_PIN);
int jstickX = 2000;

void setup()
{
    // Set pin mode
    Serial.begin(9600);
    momentaryBtn.begin();
    // jstick.calibrate(0, 4095, 500);
}

void loop()
{
    // read inputs
    momentaryBtn.read();
    jstickX = analogRead(JOY_VRX_PIN);

    if (momentaryBtn.wasPressed())
    {
        Serial.println("momentary");
    }

    if (jstickX < 1000)
    {
        Serial.println("joyLeft");
    }
    else if (jstickX > 3000)
    {
        Serial.println("joyRight");
    }
    else
    {
        Serial.println("joyNone");
    }
}
