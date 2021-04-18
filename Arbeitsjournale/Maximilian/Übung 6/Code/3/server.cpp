#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include "secret.h"

/*WiFi*/
#define PORT 3419 // choose any free port you like
WiFiServer server(PORT);

#define BTN_PIN D0
#define LED_PIN D1

void setup()
{
  Serial.begin(9600);
  pinMode(BTN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

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
    while (client.connected())
    {
      client.write(digitalRead(BTN_PIN));

      if (client.available())
      {
        digitalWrite(LED_PIN, client.read());
      }
    }
  }
  client.stop();
}