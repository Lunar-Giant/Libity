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
//SoftwareSerial controller2(10, 11);

int pressed, key;

void setup() {  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  controller1.begin(9600);
  //controller2.begin(9600);
  Keyboard.begin();
}

void loop(){
  
  if(controller1.available() > 0) {
    pressed = controller1.read();
    key = controller1.read();
  }
  
  if(pressed == 'p'){
    Serial.println(pressed);
    Serial.println(key);
    Keyboard.press(key);
  }
  /*if(controller2.read() == 'p'){
    if(controller2.read() == 'a'){
      Keyboard.press(99);
    } else {
      Keyboard.press(100);
    }
  }*/
}
