#include <Arduino.h>

void setup()
{
    // erstablish a serial connection with baud rate 9600
    // on the USB port
    Serial.begin(9600);
}

void loop()
{
    // send a string over the serial connection
    Serial.println("Hello World!");
    delay(1000);
}
