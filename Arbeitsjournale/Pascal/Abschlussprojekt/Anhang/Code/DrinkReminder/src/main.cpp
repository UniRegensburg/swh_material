/*
Required Libraries
	- Adafruit NeoPixel
*/
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Constants.h>

Adafruit_NeoPixel bottleStrip(BOTTLE_STRIP_COUNT, BOTTLE_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel glassStrip(GLASS_STRIP_COUNT, GLASS_STRIP_PIN, NEO_GRB + NEO_KHZ800);

int deviceState; // state of the device
int waterAmount_required; // the amount of water (in ml) the users should have drunk so far
int waterAmount_drunk; // the amount of water (in ml) that has been drunk so far
int waterFlow; // amount of water (in ml) pumped in the current filling process
long lastMillis; // the past milliseconds when you were reminded to drink the last time
long lastSnoozeMillis; // the past milliseconds when the snooze remind was active the last time

void initPINS(){
	pinMode(FLOW_SENSOR_PIN, INPUT);
	pinMode(PRESSURE_SENSOR_PIN, INPUT);
	pinMode(SPEAKER_PIN, OUTPUT);
	pinMode(WATER_PUMP_PIN, OUTPUT);
}
void initValues(){
	bottleStrip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
	bottleStrip.show(); // Turn OFF all pixels ASAP
	bottleStrip.setBrightness(LED_BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
	glassStrip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
	glassStrip.show(); // Turn OFF all pixels ASAP
	glassStrip.setBrightness(LED_BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
	deviceState = STANDARD;
	lastMillis = millis();
	waterAmount_required = 0;
	waterAmount_drunk = 0;
}

// method for sound
void beep(){
		tone(SPEAKER_PIN, TONE_FREQUENCY, TONE_DURATION);
}
//
void LED_loading_animation(Adafruit_NeoPixel &strip, uint32_t color, int wait){
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

void remindToDrink(){
		//LEDs rot anschalten
		// Ton einmalig abspielen
		Serial.println("Remind to drink");
}

// returns state of the glass: -1 if glass not on plate, 0 if glass on plate and empty, 1 if glass filled with water
int getGlassState() {
	int val = analogRead(PRESSURE_SENSOR_PIN);
	if(val <= THRESHOLD_NO_GLASS){
		return -1;
	}
	else if(val > THRESHOLD_NO_GLASS && val <= THRESHOLD_EMPTY_GLASS){
		return 0;
	}
	else{
		return 1;
	}
}

bool bottleEmpty(){
	// read value from flow sensor
	if (true) {
		return true;
	}
	return false;
}




void setup() {
	Serial.begin(9600);
	delay(2000);
	Serial.println("Start");
	initPINS();
	initValues();
}

// Thread option: https://create.arduino.cc/projecthub/reanimationxp/how-to-multithread-an-arduino-protothreading-tutorial-dd2c37
void loop() {
	// remind timers work independent of device status
	if (millis() - lastMillis >= REMIND_INTERVAL) { // time to remind the user to drink
		Serial.println("Alarm timer");
		remindToDrink();
		lastMillis = millis();
		lastSnoozeMillis = millis();
	}
	else if (waterAmount_drunk < waterAmount_required && millis()  - lastSnoozeMillis >= SNOOZE_INTERVAL ) { // user has not drunk enough so the snooze-remind start every two minutes (until enough water was drunk)
		Serial.println("Snooze timer");
		remindToDrink();
		lastSnoozeMillis = millis();
	}
	int glassState = getGlassState();
	switch (deviceState){
		case STANDARD:
			if( glassState== -1 ){ // no glass on plate
				deviceState = NO_GLASS;
			}
			else if ( glassState == 0 ) { // glass empty
				digitalWrite(WATER_PUMP_PIN, HIGH); // start water pump
				deviceState = RECHARGING;
			}
			else{ // glass still has water in it
				// Glas enthält noch wasser
			}
			break;

		case RECHARGING:
			if ( glassState == -1 ){
				deviceState = NO_GLASS;
			}
			 if ( bottleEmpty() ) {
				deviceState = BOTTLE_EMPTY;
			}
			else if ( waterFlow >= WATER_AMOUNT ){ //
				waterFlow = 0;
				deviceState = STANDARD;
			}
			break;

		case BOTTLE_EMPTY:
			// light up LED strip
			deviceState = STANDARD;
			break;

		case NO_GLASS:
			digitalWrite(WATER_PUMP_PIN, LOW); // stop water pump
			if ( glassState !=  -1 ) {
				deviceState = STANDARD;
			}
			break;
	}
	//delay(10);
}
