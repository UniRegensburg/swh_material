#define M5STACK_MPU6886
#include <M5Stack.h>

#define sX M5.Lcd.width()  //get lcd width
#define sY M5.Lcd.height() //get lcd height
#define mX (sX / 2)        //middle of the x-axes
#define mY (sY / 2)        //middle of the y-axes
#define rad 10             //circle radius
#define swimmer 3          //make the circle look like it floats
#define upperThresh 0.05   //upper Threshold for "level" pos
#define lowerThresh -0.05  //lower Threshold for "level" pos
#define lvlCol GREEN       //color for "level" pos
#define noLvlCol RED       //color when not "level"

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;
int pPos = 0; //initiate with 0 to avoid errors

void rePosCircle()
{
  /*
  draw black over old circle to avoid flickering on the lines
  on first draw no value given, but "just a black circle"
  */
  M5.Lcd.fillCircle(pPos, mY - (rad / 2), rad, BLACK);

  M5.IMU.getAccelData(&accX, &accY, &accZ); //values between -1 and 1 -> 0 is level

  int cPos = (accX * 1.6 * 100) + mX; //as half of the values are negative, half the screen size added to map to positive values only

  if (accX < upperThresh && accX > lowerThresh)
  {
    M5.Lcd.fillCircle(cPos, mY - (rad / 2), rad, lvlCol);
  }
  else
  {
    M5.Lcd.fillCircle(cPos, mY - (rad / 2), rad, noLvlCol);
  }

  pPos = cPos;
}

void setup()
{
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();
  M5.Lcd.clear(BLACK);
  M5.Lcd.drawLine(0, mY - rad - rad / 2 - swimmer, sX, mY - rad - rad / 2 - swimmer, WHITE);
  M5.Lcd.drawLine(0, mY + rad / 2 + swimmer, sX, mY + rad / 2 + swimmer, WHITE);
  rePosCircle();
}

void loop()
{
  rePosCircle();
  delay(50); //add delay to reduce flickering
}