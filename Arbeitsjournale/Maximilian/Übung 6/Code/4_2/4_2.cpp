#include <M5Stack.h>

long startTime = 0,
     timePassed = 0; //when timer is paused, timePassed is used to restart timer where it left off
bool counting = false;

//convert milliseconds in humand readable time
String getTime(long time)
{

  //dividers to get from milliseconds to corresponding time units
  long h = time / 360000;
  time = time - (360000 * h);
  long m = time / 60000;
  time = time - (60000 * m);
  long s = time / 1000;
  time = time - (1000 * s);
  long ms = time;

  //add leading zereos
  String hr = String(h);
  if (h < 10)
  {
    hr = "0" + hr;
  }
  String min = String(m);
  if (m < 10)
  {
    min = "0" + min;
  }
  String sec = String(s);
  if (s < 10)
  {
    sec = "0" + sec;
  }
  String mls = String(ms);
  if (ms < 10)
  {
    mls = "00" + mls;
  }
  else if (ms < 100)
  {
    mls = "0" + mls;
  }

  return (hr + ":" + min + ":" + sec + ":" + mls);
}

void displayTime()
{
  M5.Lcd.setCursor(20, 100);
  M5.Lcd.print(getTime(millis() - startTime));
}

/*
using displayTime() would not zero representation as button is not pressed at exact start time of programm
extra method to display total 0
*/
void displayStart()
{
  M5.Lcd.setCursor(20, 100);
  M5.Lcd.clear(BLACK);
  M5.Lcd.print(getTime(startTime));
}

void setup()
{
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setTextSize(4);
  displayStart();
}

void loop()
{
  M5.update(); // update Button state

//avoid unwanted input with "!counting condition"
  if (M5.BtnA.wasPressed() && !counting)
  {
    //differ between first and concurrent presses
    if (startTime > 0)
    {
      counting = true;
      startTime = millis() - timePassed; 
    }
    else
    {
      startTime = millis();
      counting = true;
    }
  }
  else if (M5.BtnB.wasPressed() && counting)
  {
    timePassed = millis() - startTime;
    counting = false;
  }
  else if (M5.BtnC.wasPressed())
  {
    counting = false;
    startTime = 0;
    timePassed = 0;
    displayStart();
  }

  if (counting)
  {
    displayTime();
  }
}