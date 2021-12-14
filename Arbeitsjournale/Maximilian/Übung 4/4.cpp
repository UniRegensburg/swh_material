// Documentation: https://www.arduino.cc/en/Reference.MouseKeyboard
// Key Reference: https://www.arduino.cc/en/Reference/KeyboardModifiers

#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>

#define X_PIN A1
#define Y_PIN A2
#define Z_PIN A3
#define BUTTON_PIN 2

void setup()
{
    Serial.begin(9600);
    pinMode(X_PIN, INPUT);
    pinMode(Y_PIN, INPUT);
    pinMode(Z_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT);

    Keyboard.begin();
}

void loop()
{
    
    int xA = analogRead(X_PIN);
    int yA = analogRead(Y_PIN);
    int zA = analogRead(Z_PIN); 

    int reset = digitalRead(BUTTON_PIN);


    Serial.println(reset);

    if( reset == HIGH){
        Keyboard.write(KEY_END); //reset course
    }
    
    Serial.print("x:");
    Serial.print(xA);
    Serial.print(" y:");
    Serial.print(yA);
    Serial.print(" z:");
    Serial.print(zA);
    Serial.println();

    // delay(1000);
    
    //drive/break values 
    if(yA >= 400){
        Keyboard.press(KEY_DOWN_ARROW);
    } else {
        Keyboard.release(KEY_DOWN_ARROW);
    }
    if(yA <= 360){
        Keyboard.press(KEY_UP_ARROW);
    } else {
        Keyboard.release(KEY_UP_ARROW);
    }

//lean forward/backward values
//single press, to adjust position of the driver. no need for constant press
    if(zA >= 400){
        Keyboard.write(KEY_LEFT_ARROW);
    }
    if(zA <= 360){
        Keyboard.write(KEY_RIGHT_ARROW);
    }
}
