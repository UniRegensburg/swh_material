#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include "secret.h"

/*WiFi*/
#define PORT 3419 // choose any free port you like
WiFiClient client;

#define BTN_PIN D0

void setup()
{
  Serial.begin(9600);
  pinMode(BTN_PIN, INPUT);

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
  int btn = digitalRead(BTN_PIN);

	if(btn == HIGH){
		client.write(btn); // send data
    delay(5500); //stop unwanted input for length of doorbell
	}
  delay(10); //standard delay

}