// inspired by http://www.esp8266learning.com/wemos-webserver-example.php
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
// enter wifi credentials here
#define SSID "SSID"
#define PW "PW"

WiFiServer server(80); // object for the WiFi server (parameter is the port)
 
void setup()
{
    Serial.begin(9600);
    delay(10);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // connect to WiFi network
    Serial.print("connecting to ");
    Serial.println(SSID);

    WiFi.begin(SSID, PW);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.println("connecting...");
    }
    Serial.println("connected!");

    server.begin();
    Serial.println("server started");

    // print the IP address
    // you can connect with any web browser!
    Serial.print("URL: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
}

void loop()
{
    // has a client connected?
    WiFiClient client = server.available();
    if (!client)
    {
        delay(10);
        return;
    }

    // wait until client sends data
    Serial.println("client connected!");
    while(!client.available())
    {
        delay(1);
    }

    // read first line of request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // process the request
    // LED_BUILTIN is inverted, so LOW means on and HIGH means off
    int ledState = LOW;
    if(request.indexOf("/LED=ON") != -1) ledState = LOW;
    if(request.indexOf("/LED=OFF") != -1) ledState = HIGH;
    digitalWrite(LED_BUILTIN, ledState);

    // return HTML of the resulting website
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");

    client.print("Led is now: ");

    if(ledState == HIGH) client.print("On");  
    else client.print("Off"); 

    client.println("<br><br>");
    client.println("Click <a href=\"/LED=ON\">here</a> to turn the LED on<br>");
    client.println("Click <a href=\"/LED=OFF\">here</a> to turn the LED off<br>");
    client.println("</html>");

    delay(10);
}
