#include <Arduino.h>
#include <ESP8266WiFi.h>

#define SSID "SSID"
#define PW "PW"
#define PORT 5555 // choose any free port you like

// we are the server
WiFiServer server(PORT);

void setup()
{
    Serial.begin(9600);

    // init WiFi object
    WiFi.mode(WIFI_STA); // STATION mode - connect to existing WiFi network
    WiFi.begin(SSID, PW);

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
                String message = client.readStringUntil('\r');
                Serial.println(message);
            }
        }
    }

    // close connection
    client.stop();

    delay(100);
}
