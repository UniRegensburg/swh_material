// Client
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "secret.h"

#define LED_PIN D1
#define BTN_PIN D2

/*WiFi*/
#define PORT 1515
WiFiClient client;
IPAddress IP(0,0,0,0);

bool isPressed;

void setup()
{
	Serial.begin(9600);
	pinMode(BTN_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
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
		Serial.println("Button gedrückt");
		isPressed = true;
		client.write(btn); // send data
	}
	else if(btn == LOW && isPressed){
		Serial.println("Button released");
		isPressed = false;
		client.write(btn); // send data
	}
	if(client.available()){
		byte received = client.read(); // received is either HIGH or LOW
		digitalWrite(LED_PIN, received);
	}
}
