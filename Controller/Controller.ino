#include <SoftwareSerial.h>

 /*
  Lunar Giant Controller

  Takes multiple custom controllers, combines their input values, and spits em back out the other end. Mothafuckaaaas!

  The circuit:
    * a joystick, which I am still not entirely sure how to get working
    * two pushbuttons attached to pins 2 - 13 from +5V
    * 10K resistors attached to pins 2 - 13 from ground
   
  created 2014
  by Jay Margalus, Zach Cassity & Russ Lankenau <http://www.lunargiant.com>
*/

/*
  Constants where the controllers will be plugged in.
  
  In use should be:
    * Buttons: D2, D3, D5, and D7-13, with 2 pins corresponding to each controller
    * Joystick: A0-A5, and D4 (A6) and D6 (A7), with 2 of each corresponding to each controller
*/

SoftwareSerial controller1(8, 9);
SoftwareSerial controller2(10, 11);

void setup() {  
  controller1.begin(9600);
  controller2.begin(9600);
  Serial.begin(9600);
  Keyboard.begin();
}

void loop(){
  int code, key;
  if (controller1.available()) {
    code = Serial.read();
    key = Serial.read();
    if (code=='p'){
      Keyboard.press(32);
    } else {
      Keyboard.press(13);
    }
    Serial.print(c);
  }
  if (controller2.available()) {
    code = controller2.read();
    key = controller2.read();
    Serial.print(c);
  }
}