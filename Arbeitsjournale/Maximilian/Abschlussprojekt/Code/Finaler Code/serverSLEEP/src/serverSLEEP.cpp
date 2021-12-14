#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include "secret.h"

/*WiFi*/
#define PORT 3419 // choose any free port you like
WiFiServer server(PORT);

#define MIC_PIN A0

//initiate variables for calculations & readings later
unsigned int mic;
unsigned long startMillis = 0; // Start of sample window
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

//loop connects mic readings, as long as they have no client is connected
//on connect, send highest amp to client for further action
void loop()
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

  
  WiFiClient client = server.available();

  if (client.connected())
  {
    peakToPeak = signalMax - signalMin; // max - min = peak-peak amplitude
    byte volume = ((peakToPeak * 255) / 1024); //convert readings between 0 and 1024 to byte rep

    //sent readings to client
    client.write(volume);

    //reset readings
    signalMax = 0;
    signalMin = 1024;
    
    //shutdown client and toss out old readings
    client.stop();
    client.flush();
  }

  delay(50);
}