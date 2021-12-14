// Documentation: https://www.arduino.cc/en/Reference.MouseKeyboard
// Key Reference: https://www.arduino.cc/en/Reference/KeyboardModifiers
#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>

#define X_ACC A1
#define Y_ACC A2
#define Z_ACC A3
#define MOUSE_MULTIPLIER 20

#define POINTERFINGER  2
#define MIDDLEFINGER 4
#define RINGFINGER 7
#define KEY_WALK 'w'

// delay of accelerometer input read
#define ACC_DELAY 20
// Mouse movement speed
#define MOUSE_SPEED 30
// Threshold values for accelerometer input
#define UPPER_THRES 355
#define LOWER_THRES 315
#define SETBLOCK_DELAY 200

int walk, attack, setBlock;
long lastMillis, lastMillis2;
bool isAttacking, isWalking;

void setup()
{
	Serial.begin(9600);
	// initialize accelerometer pins
	pinMode(X_ACC, INPUT);
	pinMode(Y_ACC, INPUT);
	pinMode(Z_ACC, INPUT);
	pinMode(POINTERFINGER, INPUT);
	pinMode(MIDDLEFINGER, INPUT);
	pinMode(RINGFINGER, INPUT);
	// make sure we have enough time to upload a new program
	delay(500);
	// initialize axis values
	Mouse.begin();
	Keyboard.begin();
	isAttacking = false;
}

void moveMouse(int x, int y){
	if(x > UPPER_THRES){
		Mouse.move(-MOUSE_SPEED, 0, 0); // move mouse right
	}
	else if(x < LOWER_THRES){
		Mouse.move(MOUSE_SPEED, 0, 0); // move mouse left
	}
	if(y > UPPER_THRES){
		Mouse.move(0, MOUSE_SPEED, 0); // move mouse down
	}
	else if(y < LOWER_THRES){
		Mouse.move(0, -MOUSE_SPEED, 0); // move mouse up
	}
}

void checkFingerInput(){
	walk = digitalRead(POINTERFINGER);
	attack = digitalRead(MIDDLEFINGER);
	setBlock = digitalRead(RINGFINGER);
	if(walk == HIGH && ! isWalking){
		isWalking = true;
		Keyboard.press(KEY_WALK);
	}
	else if(walk == LOW){
		isWalking = false;
		Keyboard.release(KEY_WALK);
	}
	if(attack == HIGH && ! isAttacking) {
		isAttacking = true;
		Mouse.press();
	}
	else if(attack == LOW){
		isAttacking = false;
		Mouse.release();
	}
	if(millis() - lastMillis2 >= SETBLOCK_DELAY){
		lastMillis2 = millis();
		if(setBlock == HIGH) {
			Mouse.click(MOUSE_RIGHT);
		}
	}
}

void loop()
{
	// simple timer --> Acc input is only read every 20ms
	if(millis() - lastMillis >= ACC_DELAY){
		lastMillis = millis();
		moveMouse(analogRead(X_ACC), analogRead(Y_ACC));
	}
	checkFingerInput();
}
