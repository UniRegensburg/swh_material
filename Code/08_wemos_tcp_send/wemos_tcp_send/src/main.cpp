#include <Arduino.h>
#include <ESP8266WiFi.h>

#define SENSOR_PIN A0

#define SSID "SSID"
#define PW "PW"
#define PORT 5555 // choose any free port you like

WiFiClient client;
IPAddress IP(192, 168, 0, 0); // change me

void setup()
{
    pinMode(SENSOR_PIN, INPUT);

    Serial.begin(9600);

    // init WiFi object
    WiFi.mode(WIFI_STA); // STATION mode - connect to existing WiFi network
    WiFi.begin(SSID, PW);

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
}

void loop()
{
    uint16_t value = analogRead(SENSOR_PIN);

    String message = "value:" + String(value); // create a message (useful when multiple values are sent

    client.print(message); // send message over the socket (don't use println() as it sends line separators)

    Serial.println(message); // print message to the console for debugging

    delay(100);
}
