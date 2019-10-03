#include <JC_Button.h>

Button momentaryBtn(5);

void setup()
{
    // Set pin mode
    Serial.begin(9600);
    momentaryBtn.begin();
}

void loop()
{
    // read inputs
    momentaryBtn.read();

    // send off the input
    if (momentaryBtn.wasPressed())
    {
        Serial.println("momentary");
    }
}
