#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define LED_COUNT 9
#define BTN_RED 2
#define BTN_BLUE 4

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// 0 schwarz, 1 rot, 2 blau, 3 lila
int leds[] = {0,0,0, 0,0,0,0,0,0};

void setup() {
	pinMode(BTN_RED, INPUT);
	pinMode(BTN_BLUE, INPUT);
	strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
	strip.show();            // Turn OFF all pixels ASAP
  	strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void shiftArrayValues(int firstVal){
	for(int i = LED_COUNT-1; i > 0; i--){
		leds[i] = leds[i-1];
	}
	// shift in first value
	leds[0] = firstVal;
}

void showLEDColors(){
	for(int i = 0; i < strip.numPixels(); i++){
		if(leds[i] == 3){
			strip.setPixelColor(i, strip.Color(255, 0, 255));
			strip.show();
		}
		else if(leds[i] == 1){
			strip.setPixelColor(i, strip.Color(255, 0, 0));
			strip.show();
		}
		else if(leds[i] == 2){
			strip.setPixelColor(i, strip.Color(0, 0, 255));
			strip.show();
		}
		else {
			strip.setPixelColor(i, strip.Color(0, 0, 0));
			strip.show();
		}
	}
}

void loop() {
	int isRed = digitalRead(BTN_RED);
	int isBlue = digitalRead(BTN_BLUE);

	if(isRed == HIGH && isBlue == HIGH){
		shiftArrayValues(3);
	}
	else if(isRed == HIGH){
		shiftArrayValues(1);
	}
	else if(isBlue == HIGH){
		shiftArrayValues(2);
	}
	else{
		shiftArrayValues(0);
	}
	showLEDColors();
	delay(100);
}
