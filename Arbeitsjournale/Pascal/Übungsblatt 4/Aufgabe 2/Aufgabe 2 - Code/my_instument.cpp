// include the Arduino standard library
#include <Arduino.h>

#define SPEAKER_PIN 2
#define LEFT_BTN_PIN 8
#define MID_BTN_PIN 7
#define RIGHT_BTN_PIN 4
#define TONE_A 440 // Kammerton a
#define TONE_C 260 // Schloss- C
#define TONE_H 987 // h''

void setup(){
	// Serial.begin(9600);
    // speaker is on out pin
	pinMode(SPEAKER_PIN, OUTPUT);
	// buttons are on input pins
	pinMode(LEFT_BTN_PIN, INPUT_PULLUP);
}

void loop(){
	// Serial.print(digitalRead(RIGHT_BTN_PIN));
	if(digitalRead(RIGHT_BTN_PIN) == HIGH){
		tone(SPEAKER_PIN, TONE_A);
	}
	else if(digitalRead(MID_BTN_PIN) == HIGH){
		tone(SPEAKER_PIN, TONE_C);
	}
	else if(digitalRead(LEFT_BTN_PIN) == HIGH){
		tone(SPEAKER_PIN, TONE_H);
	}
	else{
		noTone(SPEAKER_PIN);
	}
}
