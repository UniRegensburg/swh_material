#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include "secret.h"
#include "pitches.h"

/*WiFi*/
#define PORT 3419 // choose any free port you like
WiFiServer server(PORT);

#define SPEAKER_PIN D1

void setup()
{
  Serial.begin(9600);

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
  Serial.print("Connected. IP address: 0.0.0.0");
  // Serial.println(WiFi.localIP().toString());
}

void loop()
{
  // check for client connection
  WiFiClient client = server.available();

  //when connected
  if (client)
  {
    // read from client as long as it is connected
    while (client.connected())
    {
      if (client.available() && client.read() == HIGH)
      {
        //short doorbell melody
          tone(SPEAKER_PIN, NOTE_E5, 500);
          delay(500);
          tone(SPEAKER_PIN, NOTE_C5, 500);
          delay(500);
          tone(SPEAKER_PIN, NOTE_D5, 500);
          delay(500);
          tone(SPEAKER_PIN, NOTE_G4, 1000);
          delay(1000);
          delay(400);
          tone(SPEAKER_PIN, NOTE_G4, 500);
          delay(500);
          tone(SPEAKER_PIN, NOTE_D5, 500);
          delay(500);
          tone(SPEAKER_PIN, NOTE_E5, 500);
          delay(500);
          tone(SPEAKER_PIN, NOTE_C5, 1000);
          delay(1000);
      }
    }
  }
  // end of connect
  client.stop();
}