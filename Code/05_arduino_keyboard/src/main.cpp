// Documentation: https://www.arduino.cc/en/Reference.MouseKeyboard
// Key Reference: https://www.arduino.cc/en/Reference/KeyboardModifiers

#include <Arduino.h>
#include <Keyboard.h>

#define BUTTON_PIN 4

void setup()
{
    pinMode(BUTTON_PIN, INPUT);
    // make sure we have enough time to upload a new program
    // if something goes wrong
    delay(3000);

    Keyboard.begin();
}

void loop()
{
    // press 'a' as long as the button is down
    if(digitalRead(BUTTON_PIN) == HIGH)
    {
        // we can also send ASCII values
        Keyboard.press('a');
        delay(100);
        Keyboard.release('a');
    }
    delay(1000);
}
