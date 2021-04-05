#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include "pitches.h"

#define BTN_SQUARE_PIN 4
#define BTN_CIRCLE_PIN 5
#define BTN_TRIANGLE_PIN 6
#define SPEAKER_PIN 8
#define LED_STRIP_PIN 13

#define MAX_TIME_PERIOD 7000
#define MIN_TIME_PERIOD 1000
#define REACTION_TIME 1000

/*States*/
#define WAITING 1 // game waiting random time until shape is displayed
#define RUNNING 2 // when state = RUNNING, then the countdown for user actions started
#define WINNING 3
#define LOSING 4
/*Shapes*/
#define SQUARE 1
#define CIRCLE 2
#define TRIANGLE 3
/*Sounds*/
#define SOUND_WINNING 1
#define SOUND_LOSING 2
/*Other*/
#define MAX_SCORE 5

Adafruit_NeoPixel strip(MAX_SCORE, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

long lastMillis, reactionTimeStart;
int timePeriod, state, shape, score;

byte matrix_circle[] = {B00111100,B01000010,B10000001,B10000001,B10000001,B10000001,B01000010,B00111100};
byte matrix_square[] = {B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111};
byte matrix_triangle[] = {B00000001,B00000011,B00000101,B00001001,B00010001,B00100001,B01000001,B11111111};

// melody from: https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
int win_melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note durations of win melody
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
	Serial.begin(9600);
	timePeriod = random(MIN_TIME_PERIOD, MAX_TIME_PERIOD); // min inclusive, max exclusive
	strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  	strip.show();            // Turn OFF all pixels ASAP
  	strip.setBrightness(100);
	matrix.begin(0x71);  // find out adress: https://learn.adafruit.com/adafruit-led-backpack/changing-i2c-address
	delay(2000);
	state = WAITING;
	score = 0;
	lastMillis = millis();
}

void playSound(int sound){
	if(sound == SOUND_WINNING){
			// the played melody is copied from: https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
			for (int thisNote = 0; thisNote < 8; thisNote++) {
		    int noteDuration = 1000 / noteDurations[thisNote];
		    tone(8, win_melody[thisNote], noteDuration);
		    int pauseBetweenNotes = noteDuration * 1.30;
		    delay(pauseBetweenNotes);
		    noTone(8);
		}
	}
	else if (sound == SOUND_LOSING){
		tone(SPEAKER_PIN, NOTE_F1, 1000);
	}
	else{
		Serial.println("Can't play sound!");
	}
}



void resetStates(){ // resets the state to WAITING
	timePeriod = random(MIN_TIME_PERIOD, MAX_TIME_PERIOD);
	lastMillis = millis();
	matrix.clear();
	matrix.writeDisplay();
	state = WAITING;
}

	void updateLEDStrip(){
		Serial.print("LED Strip updaten: "); Serial.println(score);
		strip.clear();
		for(int i = 0; i < score; i++){
			strip.setPixelColor(i, strip.Color(255, 0, 0));
		}
		strip.show();
	}

	void LEDWinAnimation(){
		for(int j = 0; j < 5; j++){
			for(int i = 0; i < score; i++){
				strip.setPixelColor(i, strip.Color(0, 255, 0));
				strip.show();
			}
			delay(200);
			strip.clear();
			strip.show();
			delay(200);
		}
	}

	void resetGame(){
		score = 0;
		updateLEDStrip();
		resetStates();
	}

	void increaseScore(){
		score++;
		if(score == 5){
			LEDWinAnimation();
			resetGame();
		}
		updateLEDStrip();
}

void drawShape(int shape){
	switch(shape){
		case CIRCLE:
			Serial.print("CIRCLE");
		    matrix.drawBitmap(0, 0,matrix_circle, 8, 8, LED_ON);
		    matrix.writeDisplay();
			break;
		case SQUARE:
			Serial.print("SQUARE");
		    matrix.drawBitmap(0, 0, matrix_square, 8, 8, LED_ON);
		    matrix.writeDisplay();
			break;
	  	case TRIANGLE:
			Serial.print("TRIANGLE");
		    matrix.drawBitmap(0, 0, matrix_triangle, 8, 8, LED_ON);
		    matrix.writeDisplay();
			break;
	}
}

// returns -1 if wrong or multiple buttons pressed, 1 if right button pressed, 0 if no button pressed
int checkButtonPressed(int btnCircle, int btnSquare, int btnTriangle){
	if(btnCircle + btnSquare + btnTriangle == 0){ // no button pressed
		return 0;
	}
	else if (btnCircle + btnSquare + btnTriangle > 1){ // multiple buttons pressed
		return -1;
	}
	else if ( (btnCircle == HIGH && shape == CIRCLE) || (btnSquare == HIGH && shape == SQUARE) || (btnTriangle == HIGH && shape == TRIANGLE) ){
		return 1;
	}
	return -1; // wrong button pressed
}

void loop() {
	 int btnCircle = digitalRead(BTN_CIRCLE_PIN);
	int btnSquare = digitalRead(BTN_SQUARE_PIN);
	int btnTriangle = digitalRead(BTN_TRIANGLE_PIN);

	switch(state){
		case WAITING:
			if(btnCircle != LOW || btnSquare != LOW || btnTriangle != LOW){ // button was pressed before shape was shown --> counts as user mistake
				state = LOSING;
				Serial.println("LOSING");
			}
			else if(millis() - lastMillis >= timePeriod){ // waiting time is over / shape is shown and reaction window for user starts
				shape = random(SQUARE, TRIANGLE + 1); // +1 because max is exclusive
				state = RUNNING;
				drawShape(shape);
				lastMillis = millis();
				Serial.println("RUNNING");
			}
			break;

		case RUNNING:
			if(millis() - lastMillis >= REACTION_TIME) {
				state = LOSING;
				Serial.println("LOSING");
			}
			else{
				int result = checkButtonPressed(btnCircle, btnSquare, btnTriangle);
				if(result == -1) {
					state = LOSING;
					Serial.println("LOSING");
				}
				else if(result == 1) {
					state = WINNING;
					Serial.println("WINNING");
				}
			}
			break;

		case WINNING:
			playSound(SOUND_WINNING);
			increaseScore();
			resetStates();
			Serial.println("WAITING");
			delay(1000);
			break;

		case LOSING:
			playSound(SOUND_LOSING);
			resetGame();
			Serial.println("WAITING");
			delay(1000);
			break;
	}
}
