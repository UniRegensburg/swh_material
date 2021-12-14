#define M5STACK_MPU6886
#include <M5Stack.h>

#define CIRCLE_RADIUS 10
#define DEADZONE 2 // mögliche Pixelabweichung von der Mitte, damit Kreis immernoch farbig ist

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;
int prev_x;

int MIDDLE_Y; // Mittelpunkt auf x-Achse
int MIDDLE_X; // Mittelpunkt auf y-Achse
// the setup routine runs once when M5Stack starts up
void setup(){
	// init lcd, serial, but don't init sd card
     M5.begin();
	 Serial.begin(9600);
     M5.Power.begin();
	 M5.IMU.Init();
	 delay(100);
	 MIDDLE_X =  (int)(M5.Lcd.width()/2);
	 MIDDLE_Y =  (int)(M5.Lcd.height()/2);
	 M5.Lcd.clear(BLACK);
	 M5.Lcd.drawLine(0, MIDDLE_Y, M5.Lcd.width(), MIDDLE_Y, WHITE);
	 M5.Lcd.drawLine(MIDDLE_X, 0, MIDDLE_X, M5.Lcd.height(), WHITE);
	 M5.IMU.getAccelData(&accX, &accY, &accZ);
	 prev_x = accX;
	 M5.Lcd.fillCircle((100*accX *1.6) + MIDDLE_X, MIDDLE_Y, CIRCLE_RADIUS, WHITE);	 // init circle position

}

void drawCircle(int x){
	M5.Lcd.fillCircle(prev_x, MIDDLE_Y, CIRCLE_RADIUS, BLACK);
	M5.Lcd.drawLine(0, MIDDLE_Y, M5.Lcd.width(), MIDDLE_Y, WHITE);
	M5.Lcd.drawLine(MIDDLE_X, 0, MIDDLE_X, M5.Lcd.height(), WHITE);
	if(x >= MIDDLE_X - DEADZONE && x <= MIDDLE_X + DEADZONE){
		M5.Lcd.fillCircle(x, MIDDLE_Y, CIRCLE_RADIUS, RED);
	}
	else{
		M5.Lcd.fillCircle(x, MIDDLE_Y, CIRCLE_RADIUS, WHITE);
	}
}

// the loop routine runs over and over again forever
void loop() {
	M5.update(); // update Button state
	M5.IMU.getAccelData(&accX, &accY, &accZ);
	int x = (100*accX *1.6) + MIDDLE_X; // xPos of circle
	drawCircle(x);
	prev_x = x;
	delay(100);
}
