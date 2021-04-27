#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include <ezButton.h>

const char* ssid = "HellaBread"; //Enter SSID
const char* password = "unitedbankofmoney"; //Enter Password
const char* websockets_server = "192.168.178.35:9001"; //server adress and port

using namespace websockets;

void onMessageCallback(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
}

void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}

WebsocketsClient client;
ezButton button(D5);

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    // Connect to wifi
    WiFi.begin(ssid, password);

    // Wait some time to connect to wifi
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(1000);
    }

    // Setup Callbacks
    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);
    
    // Connect to server
    client.connect(websockets_server);
}

void loop() {
    client.poll();
    button.loop();

    if(button.isPressed()) {
      Serial.println("pressed");
      client.send("on");
    }
}
