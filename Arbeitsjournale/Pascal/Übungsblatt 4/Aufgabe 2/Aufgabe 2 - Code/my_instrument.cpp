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
    // define Modes of the Pins --> Buttons on INPUT Pins, Speaker on OUTPUT Pins
	pinMode(SPEAKER_PIN, OUTPUT);
	pinMode(LEFT_BTN_PIN, INPUT);
	pinMode(MID_BTN_PIN, INPUT);
	pinMode(RIGHT_BTN_PIN, INPUT);
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
