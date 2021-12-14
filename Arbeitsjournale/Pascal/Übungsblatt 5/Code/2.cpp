#include <Arduino.h>

#define DATA_PIN 2
#define STORE_PIN 4 // RCLK / store-clock Pin
#define SHIFT_PIN 7 // SRCLK / Shift-clock Pin / clockPin

#define SEC_PER_MIN 60
#define MS_PER_SEC 1000

byte seconds = 0;
byte minutes = 0;
long lastMillis = 0;

void setup() {
	Serial.begin(9600);
	pinMode(DATA_PIN, OUTPUT);
	pinMode(STORE_PIN, OUTPUT);
	pinMode(SHIFT_PIN, OUTPUT);
	digitalWrite(SHIFT_PIN, LOW);
}

// transforms the seconds-byte and minute-byte into one byte that can be send to the shift register
byte getOutputByte(){
	return minutes << 6 | seconds; // shift the two minute bits to the left and append the 6 bits representing the seconds
}

void updateClock(){
	seconds++;
	if(seconds == SEC_PER_MIN){
		seconds = 0;
		minutes++;
		if(minutes == 4){ // max number that can be displayed with 2 bits is 3
			minutes = 0;
		}
	}
	Serial.print(minutes); Serial.print(":"); Serial.print(seconds); Serial.println();
	digitalWrite(STORE_PIN, LOW); // set RCLK to LOW so that values do not get shifted of out register instantly
	shiftOut(DATA_PIN, SHIFT_PIN, MSBFIRST, getOutputByte());
	digitalWrite(STORE_PIN, HIGH); // send data out
}

void loop() {
	if(millis() - lastMillis >= MS_PER_SEC){
		lastMillis = millis();
		updateClock();
	}
	// space for some more code
}
