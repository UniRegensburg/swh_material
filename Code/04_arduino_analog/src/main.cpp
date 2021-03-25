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
    int sensor_brightness = analogRead(POTI_PIN);

    // map brightness from 10 bit to 8 bit
    int led_brightness = map(sensor_brightness, 0, 1023, 0, 255):

    analogWrite(LED_PIN, led_brightness);

    Serial.println(led_brightness);

    delay(100);
}
