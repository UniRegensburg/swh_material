// Client (Button)
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "secret.h"

/*WiFi*/
#define PORT 1515
WiFiClient client;
IPAddress IP(0,0,0,0); // see what IP the server connected to

#define BTN_PIN D2
bool isPressed;

void setup()
{
	Serial.begin(9600);
	pinMode(BTN_PIN, INPUT);
	isPressed = false;
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
	int btn = digitalRead(BTN_PIN);
	if(btn == HIGH && ! isPressed){
		Serial.println("ringing...");
		isPressed = true;
		client.write(btn); // send data
	}
	else if(btn == LOW){
		isPressed = false;
	}
	delay(10);
}
