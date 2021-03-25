#include <Arduino.h>

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT); // LED is connected to pin D4
}

void loop()
{
    // LED_BUILTIN is inverted, so LOW turns it on and HIGH turns it off
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
}
