#include <Arduino.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include "Secret.h"
#include <SPI.h>

/*WiFi*/
#define PORT 1515 // choose any free port number
WiFiClient client;
IPAddress IP(0,0,0,0); // IP address has to be changed

/*Sensor*/
#define DHTTYPE DHT11   // DHT 11
#define DHTPIN D4    // DHT11 connects to PIN 4 (cannot be changed)
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
	Serial.begin(9600);
	dht.begin();
	// init WiFi object
    WiFi.mode(WIFI_STA); // STATION mode - connect to existing WiFi network
    WiFi.begin(SSID, PASSWORD);

	while(WiFi.status() != WL_CONNECTED)
   {
	   Serial.println("connecting to network...");
	   delay(100);
   }

   // connect to server
   while(!client.connected())
   {
	   Serial.println("connecting to server...");
	   client.connect(IP, PORT);
	   delay(100);
   }
   Serial.println("Connected!");
}

void loop()
{
	float temperature = dht.readTemperature(); // Temperature in °C
  	float humidity = dht.readHumidity();
	// Check if any reads failed and exit early (to try again).
	if (isnan(humidity) || isnan(temperature))
	{
	    Serial.println("Cannot read sensor data!");
	    return;
  	}
  	String message = String(temperature) + " " + String(humidity); // create a message (useful when multiple values are sent
	client.print(message); // send message over the socket (don't use println() as it sends line separators)
	Serial.println(message); // print message to the console for debugging
	delay(5000); // client sends data every 2 seconds
}
