#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include "secret.h"

/*WiFi*/
#define PORT 3419 // choose any free port you like
WiFiClient client;

#define LED_PIN D1
#define LED_COUNT 3
#define THRESH 160 //og 200, divide by 2 for byte rep
#define WAIT_RNBW 3

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//color-scheme to display
void rainbow()
{
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
  {
    for (int i = 0; i < strip.numPixels(); i++)
    { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();     // Update strip with new contents
    delay(WAIT_RNBW); // Pause for a moment
  }
  strip.clear();
  strip.show();
}

void setup()
{
  Serial.begin(9600);

//init LED strip
  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(150); // Set BRIGHTNESS to about 1/5 (max = 255)

  // init WiFi object
  WiFi.mode(WIFI_STA); // STATION mode - connect to existing WiFi network
  WiFi.begin(SSID, PW);

//connect to wifi
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("connecting to network...");
    delay(50);
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
  if (client.available())
  {
    int mic = client.read();
    Serial.println(mic);

    //only trigger if noises were loud enough
    if (mic > THRESH)
    {
      rainbow();
    }

    //go into Deep-Sleep-Mode for 5 seconds to save battery-power
    ESP.deepSleep(5e6);
  }

  delay(5);
}