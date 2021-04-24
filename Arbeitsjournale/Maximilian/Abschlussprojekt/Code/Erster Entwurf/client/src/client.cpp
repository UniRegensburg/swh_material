#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include "secret.h"

/*WiFi*/
#define PORT 3419 // choose any free port you like
WiFiClient client;

#define VIB_PIN D2
#define LED_PIN D1
#define LED_COUNT 3
#define THRESH 180 //og 200, divide by 2 for byte rep
#define WAIT_SNGL 500
#define WAIT_RNBW 3

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void singleLight(uint32_t color, int ledNum)
{
  strip.setPixelColor(ledNum, color);
  strip.show();
  delay(WAIT_SNGL);
  strip.clear();
  strip.show();
}

void rainbow()
{
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
  {
    for (int i = 0; i < strip.numPixels(); i++)
    { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(WAIT_RNBW);  // Pause for a moment
  }
  strip.clear();
  strip.show();
}

void setup()
{
  Serial.begin(9600);

  pinMode(VIB_PIN, OUTPUT);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(150); // Set BRIGHTNESS to about 1/5 (max = 255)

  // init WiFi object
  WiFi.mode(WIFI_STA); // STATION mode - connect to existing WiFi network
  WiFi.begin(SSID, PW);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("connecting to network...");
    delay(100);
  }

  // connect to server
  while (!client.connected())
  {
    Serial.println("connecting to server...");
    client.connect(IP, PORT);
    delay(100);
  }
  Serial.println("Connected!");
}

void loop()
{

  // Serial.println(client.read());

  if (client.available())
  {
    int mic = client.read();
    Serial.println(mic);

    if (mic > THRESH)
    {
      // singleLight(strip.Color((rand() % 255), (rand() % 255), (rand() % 255)),  0);
      rainbow();
    }
  }

  delay(5);
}