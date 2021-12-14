// Server (Lautsprecher)
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "secret.h"

#define PORT 1515 // choose any free port you like
#define SPEAKER_PIN D1

// we are the server
WiFiServer server(PORT);

void setup()
{
    Serial.begin(9600);
	pinMode(SPEAKER_PIN, OUTPUT);
    // init WiFi object
    WiFi.mode(WIFI_STA); // STATION mode - connect to existing WiFi network
    WiFi.begin(SSID, PASSWORD);
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.println("connecting to network...");
        delay(100);
    }
    server.begin();
    // print IP of this device so someone else can connect
    Serial.print("Connected. IP address: ");
    Serial.println(WiFi.localIP().toString());
}

void loop()
{
    // check if someone wants to connect
    WiFiClient client = server.available();
    if(client)
    {
        // read from client as long as it is connected
        while(client.connected())
        {
            // has the client sent something?
            if(client.available())
            {
                // read message until terminator sequence
				byte btnPressed = client.read();
                if(btnPressed == HIGH){
					tone(SPEAKER_PIN, 500, 1000);
				}
            }
        }
    }
    // close connection
    client.stop();
    delay(100);
}
