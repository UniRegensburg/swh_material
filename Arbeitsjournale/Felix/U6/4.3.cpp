// define must ahead #include <M5Stack.h>
#define M5STACK_MPU6886 
// #define M5STACK_MPU9250 
// #define M5STACK_MPU6050
// #define M5STACK_200Q

#include <M5Stack.h>

float pitch = 0.0F;
float roll = 0.0F;
float yaw = 0.0F;

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
    
  M5.IMU.Init();

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN , BLACK);
  M5.Lcd.setTextSize(2);
}

// the loop routine runs over and over again forever
void loop() {
    // put your main code here, to run repeatedly:
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);

//320x240
  M5.Lcd.clear();

  int color = 0XFF00FF;
  if ((int)pitch < 5 && (int)pitch > -5 && (int)roll < 5 && (int)pitch > -5)
  {
    color = 0X0000FF;
}

  m5.Lcd.drawCircle(160+(int)pitch, 120+(int)roll, 10, color);

  delay(1);
}

