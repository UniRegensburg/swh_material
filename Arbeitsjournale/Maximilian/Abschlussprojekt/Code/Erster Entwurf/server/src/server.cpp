#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include "secret.h"

/*WiFi*/
#define PORT 3419 // choose any free port you like
WiFiServer server(PORT);

#define MIC_PIN A0

//mic values

unsigned int mic;

unsigned long startMillis = 0; // Start of sample window
unsigned long currentMillis = 0;
unsigned int peakToPeak = 0; // peak-to-peak level

unsigned int signalMax = 0;
unsigned int signalMin = 1024;

void setup()
{
  Serial.begin(9600);
  pinMode(MIC_PIN, INPUT);

  // init WiFi object
  WiFi.mode(WIFI_STA); // STATION mode - connect to existing WiFi network
  WiFi.begin(SSID, PW);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("connecting to network...");
    delay(100);
  }

  server.begin();
  // print IP of this device so someone else can connect
  Serial.print("Connected. IP address:");
  Serial.println(WiFi.localIP().toString());
}

void loop()
{
  // check for client connection
  WiFiClient client = server.available();
  //when connected
  if (client)
  {
    startMillis = millis(); // Start of sample window
    while (client.connected())
    {
      if (millis() - startMillis >= 150)
      {
        peakToPeak = signalMax - signalMin;       // max - min = peak-peak amplitude
        double v = ((peakToPeak * 5.1) / 1024); // convert to volts, maximum 5.1 -> better than cal with 2.55, gave me some anomalie          
        byte volume = (v * 100)/2;        // convert to transferrable byte between 0 and 255

        Serial.println(volume);

        client.write(volume);
        signalMax = 0;
        signalMin = 1024;
        startMillis = millis();
      }
      else
      {
        mic = analogRead(MIC_PIN);
        if (mic < 1024) // toss out spurious readings
        {
          if (mic > signalMax)
          {
            signalMax = mic; // save just the max levels
          }
          else if (mic < signalMin)
          {
            signalMin = mic; // save just the min levels
          }
        }
      }
      delay(10); //LOW DELAY, otherwise weird values -> needed, otherwise DTS soft reset
    }
  }
  client.stop();
  delay(100);
}