#include <Arduino.h>

// only ADC pins can be used for analog input
#define POTI_PIN A2
// only PWM pins can be used for analog output
#define LED_PIN 10

void setup()
{
    pinMode(POTI_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    // analogRead() returns a value between 0 and 1023
    int brightness = analogRead(POTI_PIN);

    analogWrite(LED_PIN, brightness);

    Serial.println(brightness);

    delay(100);
}
