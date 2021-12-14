#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6    //Pin Connect on Arduino

#define LED_COUNT 6 //Length of LED Strip (Nr. of LED's)

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void singleLight(uint32_t color, int wait, int ledNum)
{
  strip.setPixelColor(ledNum, color);
  strip.show();
  delay(wait);
  strip.clear();
}

void setup()
{

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop()
{
  for (int i = 0; i < LED_COUNT; i ++)
  {
    singleLight(strip.Color((rand() % 255), (rand() % 255), (rand() % 255)), 1000, i);
  }
}
