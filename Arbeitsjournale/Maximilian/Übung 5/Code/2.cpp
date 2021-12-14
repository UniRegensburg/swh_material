#include <ARDUINO.h>

#define shiftPin 8
#define storagePin 9
#define dataPin 11

long lastMillis = 0;
byte seconds = 0,
     minutes = 0;

void setup()
{
  Serial.begin(9600);
  // Pins 8,9,11 auf Ausgabe stellen
  pinMode(storagePin, OUTPUT);
  pinMode(shiftPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  digitalWrite(shiftPin, LOW);
}

//first tranformation function
int timer(){
  if(minutes == 0){
    return seconds;
  } else if(minutes == 1){
    return seconds + 64;
  } else if(minutes == 2){
    return seconds + 128;
  } else {
    return seconds + 128 + 64;
  }
}

//after some research, most people use bitwise operators for bitwise hardware. 
//so I adapted the method to properly use bitwise operations. Looks a lot better
//and works just the same.
byte time()
{
    return minutes << 6 | seconds;

}
void loop()
{
  if (millis() - lastMillis >= 1000)
  {
    lastMillis = millis();
    digitalWrite(storagePin, LOW);
    shiftOut(dataPin, shiftPin, MSBFIRST, time());
    digitalWrite(storagePin, HIGH);

    if (seconds >= 60)
    {
      minutes++;
      if(minutes > 3){
        minutes = 0;
      }
      seconds = 0;
    }
    else
    {
      seconds++;
    }
  }


  // Other code (as per task)
}