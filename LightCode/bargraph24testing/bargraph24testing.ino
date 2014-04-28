/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED 24 Bargraph Backpack
  ----> http://www.adafruit.com/products/721

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_24bargraph bar = Adafruit_24bargraph();
int yellbutt = 3;
int redbutt = 2;

int yellbuttstate = 0;
int redbuttstate = 0;

int count = 0;
int prevbuttpress = 0;
int prevbuttpress2 = 0;

uint8_t b = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("HT16K33 Bi-Color Bargraph test");
  
  bar.begin(0x70);  // pass in the address

  //for (uint8_t b=0; b<24; b++ ){
   // if ((b % 3) == 0)  bar.setBar(b, LED_RED);
   // if ((b % 3) == 1)  bar.setBar(b, LED_YELLOW);
   // if ((b % 3) == 2)  bar.setBar(b, LED_GREEN);
  //}
  bar.writeDisplay();
 // delay(2000);
  
   pinMode(yellbutt, LOW);
  pinMode(redbutt, LOW);
}


void loop() {
  
   yellbuttstate = digitalRead(yellbutt);
  redbuttstate = digitalRead(redbutt);
  
  
  if (yellbuttstate == HIGH)
  {
  if (count == 0)
     bar.setBar(b, LED_RED);
  if (count == 1)
  {
     bar.setBar(b, LED_OFF);
     bar.setBar(b, LED_YELLOW);
  }
  if (count == 2)
   {
     bar.setBar(b, LED_OFF);
     bar.setBar(b, LED_GREEN);
   }
  bar.writeDisplay();
    delay(50);
  // bar.setBar(b, LED_OFF);
  // bar.writeDisplay();
   b++;
   }
   
    if (redbuttstate == HIGH)
  { 
  if (count == 0) 
  bar.setBar(b, LED_OFF);
  if (count == 1)
  {
    bar.setBar(b, LED_OFF);
    bar.setBar(b, LED_RED);
    //
  }
  if (count == 2)
  {
    bar.setBar(b, LED_YELLOW);
   // bar.setBar(b, LED_OFF);
  } 
 
 
   bar.writeDisplay();
   delay(50);
  // bar.setBar(b, LED_OFF);
  // bar.writeDisplay();
   b--;
  }
 
 // Serial.println(b);
 
  if (b == 24) 
  { count = min(count+1, 2);
    b=0;
  }
  if (count == 1 && b == 0 && redbuttstate == HIGH)
  {
    count --;
    b=24;
  }
  if (count == 2 && b == 0 && redbuttstate == HIGH)
  {
    count --;
    b=24;
  }
  if ( b > 24 && count ==3)
    b=24;
  /*if (yellbuttstate == HIGH )
    {
      
      Serial.println ("YellowAgain");
  bar.setBar (b, LED_YELLOW);
  bar.writeDisplay();
  delay(50);
  b++;
}
*/
  }

//*/


  
  /*
 for (uint8_t b=0; b<24; b++) {
   bar.setBar(b, LED_RED);
   bar.writeDisplay();
   //delay(50);
   bar.setBar(b, LED_OFF);
   bar.writeDisplay();
 }
  for (uint8_t b=0; b<24; b++) {
   bar.setBar(b, LED_GREEN);
   bar.writeDisplay();
   //delay(50);
   bar.setBar(b, LED_OFF);
   bar.writeDisplay();
 }

 for (uint8_t b=0; b<24; b++) {
   bar.setBar(23-b, LED_YELLOW);
   bar.writeDisplay();
   //delay(50);
   bar.setBar(23-b, LED_OFF);
   bar.writeDisplay();
 }*/
//  }
  
  

