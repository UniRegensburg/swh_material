#include <M5Stack.h>

#define XPOS 50
#define YPOS 100

#define WAITING 0
#define RUNNING 1
int STATE;

long timeInMillis; // the time that is displayed on
long lastMillis;

// converts the milliseconds to a String of format min:sec:ms
// String always has same length: min and sec have 2 digits, ms has 3
String formatTime(long time){
	String minString, secString, msString;
	int min = time / 60000;
	time -= 60000*min;
	int sec = time / 1000;
	time -= 1000*sec;
	int ms = time;
	minString = String(min);
	secString = String(sec);
	msString = String(ms);
	if(min < 10){
		minString = "0" + minString;
	}
	if(sec < 10){
		secString = "0" + secString;
	}
	if(ms < 10){
		msString = "00" + msString;
	}
	else if (ms < 100){
		msString = "0" + msString;
	}
	return minString + ":" + secString + ":" + msString;
}

// reset the stopwatch
void displayTime(){
	M5.Lcd.setCursor(XPOS, YPOS);
	M5.Lcd.print(formatTime(timeInMillis));
}

// the setup routine runs once when M5Stack starts up
void setup(){
	timeInMillis = 0;
	STATE = WAITING;
	// init lcd, serial, but don't init sd card
     M5.begin(true, false, true);
     M5.Power.begin();
     M5.Lcd.clear(BLACK);
     M5.Lcd.setTextColor(WHITE, BLACK); // Important: BLACK background color of text prevents flickering
     M5.Lcd.setTextSize(4);
     M5.Lcd.setCursor(XPOS, YPOS);
	 displayTime();
}

// the loop routine runs over and over again forever
void loop() {
	M5.update(); // update Button state
	switch(STATE){
		case WAITING:
			if(M5.BtnB.wasPressed()){
				timeInMillis = 0;
				displayTime();
			}
			else if(M5.BtnA.wasPressed()){
				STATE = RUNNING;
				lastMillis = millis();
			}
			break;
		case RUNNING:
			if(M5.BtnB.wasPressed()){
				timeInMillis = 0;
				displayTime();
				STATE = WAITING;
			}
			else if(M5.BtnC.wasPressed()){
				STATE = WAITING;
			}
			else{
				timeInMillis += millis() - lastMillis;
				lastMillis = millis();
				displayTime();
			}
			break;
	}
}
