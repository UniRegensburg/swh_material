#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT 9

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void runFromSideToSide(uint32_t color, int wait){
	for(int i = 0; i < strip.numPixels(); i++){
		strip.clear();
		strip.setPixelColor(i, color);
		strip.show();
		delay(wait);
	}
	for(int i = strip.numPixels()-2; i > 0; i--){
		strip.clear();
		strip.setPixelColor(i, color);
		strip.show();
		delay(wait);
	}
}

void loop() {
	runFromSideToSide(strip.Color(255, 0, 0), 40);
}
