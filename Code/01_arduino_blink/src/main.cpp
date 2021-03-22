// include the Arduino standard library
#include <Arduino.h>

// this function is called once upon startup of the Arduino
void setup()
{
    // pin 13 is connected to the internal LED of the Arduino
    // define it as an output pin so we can write to it
    pinMode(13, OUTPUT);
}

// this function is looped indefinitely after setup() is finished
void loop()
{
    digitalWrite(13, HIGH); // set the voltage of pin 13 to HIGH (5V) so the LED turns on
    delay(100);            // wait for 1000 milliseconds
    digitalWrite(13, LOW);  // set the voltage of pin 13 to LOW (0V)
    delay(100);            // wait for 1000 milliseconds
}
