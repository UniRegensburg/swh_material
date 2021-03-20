#include <Arduino.h>

// define a constant for the pin number
// so we don't use magic numbers in the code
#define BUTTON_PIN 4

void setup()
{
    // we want to read the button's state
    // so we need an input pin
    pinMode(BUTTON_PIN, INPUT);

    Serial.begin(9600);
}

void loop()
{
    // read the voltage of the pin and assign it to a variable
    // digitalRead() can only return 0 or 1
    bool buttonState = digitalRead(BUTTON_PIN);

    Serial.println(buttonState);
}
