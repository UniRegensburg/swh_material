// inspired by https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
// enter wifi credentials here
#define SSID "SSID"
#define PW "PW"
#define URL "http://192.168.XX.YY:5000/"
 
void setup ()
{
    Serial.begin(9600);
    WiFi.begin(SSID, PW);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.println("connecting...");
    }
    Serial.println("connected!");
}

void loop()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("create HTTP object...");
        HTTPClient http;
        http.begin(URL);

        Serial.println("send request...");
        int httpResponse = http.GET();

        Serial.print("response code: ");
        Serial.println(httpResponse);

        if (httpResponse > 0)
        {
            Serial.print("payload: ");
            Serial.println(http.getString());
        }

        http.end();
        Serial.println("finished!");
    }

    delay(3000);
}
