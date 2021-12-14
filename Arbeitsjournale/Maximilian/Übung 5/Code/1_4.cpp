#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6    //Pin Connect on Arduino
#define BUTTON_PIN 2 // button pin on arduino

#define LED_COUNT 5 //Length of LED Strip (Nr. of LED's)

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

long lastMillis = 0;
int intervall = 500;
uint32_t off = strip.Color(0, 0, 0);

void runLight(uint32_t color)
{
  int runInc = 1;

  while (runInc <= LED_COUNT)
  {
    if (millis() - lastMillis >= intervall)
    {
      lastMillis = millis();
      strip.setPixelColor(runInc, strip.getPixelColor(runInc - 1));
      strip.show();
      runInc++;
      strip.setPixelColor(0, color);
      strip.show();
    }
  }
}

void setup()
{
  pinMode(BUTTON_PIN, INPUT);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop()
{

  int digR = digitalRead(BUTTON_PIN);

  if (millis() - lastMillis >= intervall)
  {
    lastMillis = millis();
    
    if (digR == HIGH)
    {
      runLight(strip.Color((rand() % 255), (rand() % 255), (rand() % 255)));
    }
    else
    {
      runLight(off);
    }
  }
}