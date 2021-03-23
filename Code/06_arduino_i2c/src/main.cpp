// sample for reading 2 bytes of sensor data from a connected I²C device
// would for example work with a BH1750 luxmeter
//
// you don't have to know this for the course as libraries do the heavy lifting,
// but it might be useful for more sophisticated projects

#include <Arduino.h>
#include "Wire.h"

#define ADDR 0x23 // I2C address of the sensor

void setup()
{
    Serial.begin(9600);

    Wire.begin(); // init I2C library

    delay(200); // wait for the sensor to start

    // send init command to sensor
    Wire.beginTransmission(ADDR);
    Wire.write(0x10); // init command
    Wire.endTransmission();
}

void loop()
{
    int length = 2; // length of received data in bytes
    char* data = (char*) malloc(length); // allocate 2 bytes of memory

    // get data from sensor
    Wire.beginTransmission(ADDR);
    Wire.requestFrom(ADDR, length);
    
    int i = 0;
    while(Wire.available() && i < length) 
    {
        data[i] = Wire.read(); // read one byte
        i++;
    }
    
    Wire.endTransmission(); 
    
    // convert two separate bytes to one 16 bit unsigned int
    uint16_t value = ((data[0] << 8) | data[1]);
    free(data); // we don't need the memory anymore

    Serial.println(value);
    delay(1000);
}
