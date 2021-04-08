#include <Arduino.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>

#define DHTTYPE DHT11   // DHT 11
#define DHTPIN D4    // DHT11 connects to PIN 4 (cannot be changed)

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  delay(2000);
}

void loop()
{
  float humidity = dht.readHumidity();
  float temp_c = dht.readTemperature(); // Temperature in °C
  float temp_f = dht.readTemperature(true); // Temperature in Farenheit

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temp_c) || isnan(temp_f))
  {
    Serial.println("Cannot read sensor data!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%, \t");
  Serial.print("Temperature: ");
  Serial.print(temp_c);
  Serial.print(" *C, (");
  Serial.print(temp_f);
  Serial.println(" *F)");

  delay(1000);
}
