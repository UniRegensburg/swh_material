#include <Arduino.h>

// Photoresistor
#define PR A2
// only PWM pins can be used for analog output
#define LED_PIN 10

void setup()
{
    pinMode(PR, INPUT);
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
	// analogRead() returns a value between 0 and 1023
    int value = 1023 - analogRead(PR);
	// analogWrite() can only write values between 0 and 255
    analogWrite(LED_PIN, value / 4);
    Serial.println(value / 4);
    delay(100);
}
