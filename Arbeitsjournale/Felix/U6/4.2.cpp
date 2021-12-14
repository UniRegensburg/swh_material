#include <M5Stack.h>

bool timer_started = false;
int time_count = 0;
int secCount = 0;

// the setup routine runs once when M5Stack starts up
void setup(){

  // Initialize the M5Stack object
  M5.begin();

  /*
    Power chip connected to gpio21, gpio22, I2C device
    Set battery charging voltage and current
    If used battery, please call this function in your project
  */
  M5.Power.begin();
    M5.Lcd.setTextColor(YELLOW);
  // LCD display
    drawClock("0 sec");
}

void drawClock(String val) {
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(65, 10);
  M5.Lcd.println("Stoppuhr");
  M5.Lcd.setCursor(65, 30);
  M5.Lcd.println(val);
}

// the loop routine runs over and over again forever
void loop() {
 M5.update();
 
  // if you want to use Releasefor("was released for"), use .wasReleasefor(int time) below
  if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
    timer_started = true;
  }

  if (M5.BtnB.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
    timer_started = false;
  }

  if (M5.BtnC.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
    if(!timer_started) {
      drawClock("0 sec");
    }
  }
if(timer_started) {
  if(millis() - time_count > 1000) {
    time_count = millis();
    secCount++;
    drawClock(String(secCount)+ " sec");
  }
}

}