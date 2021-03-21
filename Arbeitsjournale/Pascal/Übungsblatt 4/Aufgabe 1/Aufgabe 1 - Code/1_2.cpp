// include the Arduino standard library
#include <Arduino.h>

/*
digitalWrite(): kann nur LOW (0V) oder HIGH (5V) ausgeben
analogWrite(): kann die Spannung auf Werte zwischen 0 (0V) und 255 (5V) setzen
*/

//
int led_red = 2;
// this function is called once upon startup of the Arduino
void setup()
{
    // define it as an output pin so we can write to it
    pinMode(led_red, OUTPUT);
}

// duration is in milliseconds
void blink(int pin, int duration){
	digitalWrite(pin, HIGH); // set the voltage of pin to HIGH (5V)
	delay(duration);
	digitalWrite(pin, LOW);  // set the voltage of pin to LOW (0V)
	delay(duration);
}

// this function is looped indefinitely after setup() is finished
void loop()
{
   blink(led_red, 200);
}
