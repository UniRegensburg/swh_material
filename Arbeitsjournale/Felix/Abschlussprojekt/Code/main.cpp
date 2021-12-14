#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <ezButton.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// PROGMEM on Wemos
#define PROGMEM   ICACHE_RODATA_ATTR

#define TIME_BTW_READINGS 180000
#define NUM_READINGS 40
#define BUZZER D5

// enter wifi credentials here
#define SSID "xxx"
#define PW "xxx"
#define URL_VALUE "http://192.168.xx.xx:5000/value"
#define URL_REF "http://192.168.xx.xx:5000/ref"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix(); // Adafruit matrix
byte gy30ICAdress = 0x23; // Light sensor i2c address 
byte buffer[2]; // array to buffer sensor data

void setup() {
    /**
     * Init services
     */
    Serial.begin(9600);
    Serial.println("Sonnenmesser");

    // start i2c and sensor
    Wire.begin();
    initSensor();

    // setup wifi
    WiFi.mode(WIFI_STA);
    wifi_set_sleep_type(LIGHT_SLEEP_T);
    WiFi.begin(SSID, PW);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.println("connecting...");
    }
    Serial.println("connected!");

    // init the matrix
    matrix.begin(0x73);  // pass in the address

    /**
     * Start the routine by sending the REF data
     */
    startSample();

}

// PROGMEM bitmaps
static const uint8_t PROGMEM
  sun_small_bmp[] =
  { B00000000,
    B01000010,
    B00011000,
    B00111100,
    B00111100,
    B00011000,
    B01000010,
    B00000000 },
    sun_big_bmp[] =
  { B10000001,
    B00000000,
    B00011000,
    B00111100,
    B00111100,
    B00011000,
    B00000000,
    B10000001 },
    check_bmp[] =
    {
      B00000000,
      B00000010,
      B00000100,
      B00001000,
      B01010000,
      B00100000,
      B00000000,
      B00000000
    };

/**
 * Send a value reading to the server
 */
void sendValue(int v) {
  if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("create HTTP object...");
        HTTPClient http;
        http.begin(URL_VALUE);
        http.addHeader("Content-Type", "application/json");

        Serial.println("send request...");
        StaticJsonDocument<16> doc;
        doc["value"] = v;
        String json;
        serializeJson(doc, json);
        
        int httpResponse = http.POST(json);

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
}

/**
 * Send a reference reading to the server
 */
void sendRef(int v) {
  if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("create HTTP object...");
        HTTPClient http;
        http.begin(URL_REF);
        http.addHeader("Content-Type", "application/json");

        Serial.println("send request...");
        StaticJsonDocument<16> doc;
        doc["value"] = v;
        String json;
        serializeJson(doc, json);
        
        int httpResponse = http.POST(json);

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
}

/**
 * Reads the sensor and pushes the data to the server
 */
void startRoutine() {
    int value = 0;
    if (readSensor() == 2){
        value = ((buffer[0] << 8) | buffer[1]);
        Serial.println(value);
        sendValue(value);
    } 

    // give short visual feedback
    matrix.clear();
    matrix.drawBitmap(0, 0, sun_small_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(100);
    matrix.clear();
    matrix.drawBitmap(0, 0, sun_big_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(100);
    matrix.clear();
}

/**
 * Takes the average of 12 readings for a reference and pushes it to the server
 */
void startSample() {
    Serial.println("starting sample");
    
    int values[12];
    int valueSum = 0;
    for(int i = 0; i <= 12; i++) {
        matrix.clear();
        matrix.drawBitmap(0, 0, sun_small_bmp, 8, 8, LED_ON);
        matrix.writeDisplay();
        delay(2500);

        matrix.clear();
        matrix.drawBitmap(0, 0, sun_big_bmp, 8, 8, LED_ON);
        matrix.writeDisplay();

        int value = 0;
        if (readSensor() == 2){
        value = ((buffer[0] << 8) | buffer[1]);
        Serial.print("sample value added: "); Serial.println(value);
        values[i] = value;
        } 
        delay(2500);
    }

    for(int j = 0; j <= 12; j++) {
        valueSum = valueSum + values[j];
    }

    
    Serial.print("Ref value: "); Serial.println(valueSum / 12);
    sendRef(valueSum / 12);

    matrix.clear();
    matrix.drawBitmap(0, 0, check_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(1000);
}

/**
 * Starts the i2c light sensor
 */
void initSensor(){
    Wire.beginTransmission(gy30ICAdress);
    Wire.write(0x10); // set resolution
    Wire.endTransmission();
}

/**
 * Reads a value from the sensor
 */
int readSensor(){
    byte value = 0;
    Wire.beginTransmission(gy30ICAdress);
    Wire.requestFrom(gy30ICAdress, 2);
    while(Wire.available()){
        buffer[value] = Wire.read();
        value++;
    }
    Wire.endTransmission();
    return value;
}

/**
 * Finish routine: plays a sound and goes into loop; turns of WiFi
 */
void finish() {
    WiFi.mode(WIFI_OFF); 
    
    matrix.clear();
    matrix.drawBitmap(0, 0, check_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();

    for(int i = 0; i >= 3; i++) {
        tone(BUZZER, 1000);
        delay(200);
        tone(BUZZER, 1500);
        delay(200);
        noTone(BUZZER);
        delay(500);
    }


    while(true) {
        delay(100);
    }
}

void loop() {
    matrix.clear();
    // takes the readings
    for(int i = 0; i >= NUM_READINGS; i++) {
        startRoutine();
        delay(TIME_BTW_READINGS); // delay instead of time bc of Wemos light sleep
    }

    finish();
}