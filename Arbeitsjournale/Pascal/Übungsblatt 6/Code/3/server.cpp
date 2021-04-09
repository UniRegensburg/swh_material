// Server
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "secret.h"

#define PORT 1515 // choose any free port you like
#define LED_PIN D1
#define BTN_PIN D2

bool isPressed;

// we are the server
WiFiServer server(PORT);

void setup(){
    Serial.begin(9600);
	isPressed = false;
	pinMode(LED_PIN, OUTPUT);
	pinMode(BTN_PIN, INPUT);
    // init WiFi object
    WiFi.mode(WIFI_STA); // STATION mode - connect to existing WiFi network
    WiFi.begin(SSID, PASSWORD);

    while(WiFi.status() != WL_CONNECTED){
        Serial.println("connecting to network...");
        delay(100);
    }
    server.begin();

    // print IP of this device so someone else can connect
    Serial.print("Connected. IP address: ");
    Serial.println(WiFi.localIP().toString());
}

void loop(){
    WiFiClient client = server.available(); // check in each iteration if a client wants to connect
    if(client){ // if no client is connected, this part is skipped
        while(client.connected()){ // read from client as long as it is connected
			int btn = digitalRead(BTN_PIN);
			if(btn == HIGH && ! isPressed){
				isPressed = true;
				Serial.println("send high");
				client.write(HIGH);
			}
			else if(btn == LOW && isPressed){
				isPressed = false;
				Serial.println("send low");
				client.write(LOW);
			}
            if(client.available()){ // check if client sent something
				byte received = client.read(); // received is either HIGH or LOW
                digitalWrite(LED_PIN, received);
            }
        }
    }
    // close connection
    client.stop();
    delay(100);
}
