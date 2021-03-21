// include the Arduino standard library
#include <Arduino.h>

/*
digitalWrite(): kann nur LOW (0V) oder HIGH (5V) ausgeben
analogWrite(): kann die Spannung auf Werte zwischen 0 (0V) und 255 (5V) setzen
*/

// Represented values: left = 4, mid = 2, right = 1
int left = 2, mid = 4, right = 7;
int count = 0;
int residual = count;
// this function is called once upon startup of the Arduino
void setup()
{
    // define it as an output pin so we can write to it
    pinMode(left, OUTPUT);
	pinMode(mid, OUTPUT);
	pinMode(right, OUTPUT);
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
	residual = count;
	if(residual >= 4) {
		digitalWrite(left, HIGH);
		residual -= 4;
	}
	else{
		digitalWrite(left, LOW);
	}
	if(residual >= 2) {
		digitalWrite(mid, HIGH);
		residual -= 2;
	}
	else{
		digitalWrite(mid, LOW);
	}
	// 2**0
	if(residual == 1){
		digitalWrite(right, HIGH);
		residual -= 1;
	}
	else{
		digitalWrite(right, LOW);
	}
	// hochzählen bzw. ggf zurücksetzen
	count++;
	if(count == 8) count = 0;
	delay(1000); // delay one second
}
