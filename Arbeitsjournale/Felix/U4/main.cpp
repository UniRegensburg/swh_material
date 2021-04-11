#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <ezButton.h>

#define BTN_L 2
#define BTN_R 3
#define SHIFT 4

ezButton btn_l(BTN_L);
ezButton btn_r(BTN_R);
ezButton btn_s(SHIFT);

void setup() {
  delay(3000);

  Keyboard.begin();
  Mouse.begin();

  Serial.begin(9600);
  Serial.println("starting emulator..");
  btn_l.setDebounceTime(50);
  btn_r.setDebounceTime(50);
  btn_s.setDebounceTime(50);
}

void loop() {
  btn_l.loop();
  btn_r.loop();
  btn_s.loop();

  bool btn_l_state = btn_l.isPressed();
  bool btn_r_state = btn_r.isPressed();
  bool btn_s_state = digitalRead(SHIFT);

  if(btn_l_state) {
    if(btn_s_state) {
      Keyboard.write(119);
    } else {
      Mouse.move(-40, 0);
    }
  }

  if(btn_r_state) {
    if(btn_s_state) {
      Mouse.click(MOUSE_LEFT);
    } else {
      Mouse.move(40, 0);
    }
  }

  delay(10);
}