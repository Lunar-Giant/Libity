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

const int DIRECTION_NORTH = 1;
const int DIRECTION_NORTH_EAST= 2;
const int DIRECTION_EAST = 3;
const int DIRECTION_SOUTH_EAST = 4;
const int DIRECTION_SOUTH = 5;
const int DIRECTION_SOUTH_WEST = 6;
const int DIRECTION_WEST = 7;
const int DIRECTION_NORTH_WEST = 8;

/*
  Constants where the controllers will be plugged in.
  
  In use should be:
    * Buttons: D2, D3, D5, and D7-13, with 2 pins corresponding to each controller
    * Joystick: A0-A5, and D4 (A6) and D6 (A7), with 2 of each corresponding to each controller
*/
const int buttonPin = 8;
const int buttonPin2 = 9;
const int buttonPin3 = 10;
const int buttonPin4 = 11;
const int buttonPin5 = 12;
const int buttonPin6 = 13;
const int joyPin1 = 0;
const int joyPin2 = 1;
const int joyPin3 = 2;
const int joyPin4 = 3;
const int joyPin5 = 4;
const int joyPin6 = 5;

// vars for reading when pushbuttons 1-8 have been pressed
int buttonState = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
int buttonState6 = 0;
// end vars for reading when pushbuttons 1-8 have been pressed

// vars for reading when joysticks are being used
int joystick1x = 0;
int value2 = 0;
int value3 = 0;
int value4 = 0;
int value5 = 0;
int value6 = 0;
// end vars for reading when joysticks are being used

// vars for reading the time at which the first button was pressed
unsigned long buttonTime = 0;
unsigned long buttonTime2 = 251;
unsigned long buttonTime3 = 502;
// vars for second button
unsigned long buttonTime4 = 0;
unsigned long buttonTime5 = 251;
unsigned long buttonTime6 = 502;
//highest and lowest time value of button pushed
unsigned long lowest = 0;
unsigned long highest = 0;
unsigned long middle = 0;
// end vars for reading the time at which a button was pressed

int buttonA = 32;
int buttonB = 32;

// other variables
unsigned long time;                              // track the time
unsigned long interval = 250;                    // the time difference by which buttons can be pressed
int i = 0;                                       // my crappy counter for the max/min thing
int previousStick = 0;
int randNumber;

void setup() {
  
  // initialize pushbutton pins as an inputs:
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  
  Serial.begin(9600);
  Keyboard.begin();
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  joystick1x = analogRead(joyPin1);
  delay(10);
  value2 = analogRead(joyPin2);
  delay(10);
  value3 = analogRead(joyPin3);
  delay(10);
  value4 = analogRead(joyPin4);
  delay(10);
  value5 = analogRead(joyPin5);
  delay(10);
  value6 = analogRead(joyPin6);
  time = millis();
  
  // program it so that the average dictates the chance of up, down, left, or right firing.

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  
  if (buttonState == HIGH) {       
    buttonTime = time; 
  }
  if (buttonState2 == HIGH) {       
    buttonTime2 = time; 
  }
  if (buttonState3 == HIGH) {       
    buttonTime3 = time; 
  }
  if (buttonState4 == HIGH) {       
    buttonTime4 = time; 
  }
  if (buttonState5 == HIGH) {       
    buttonTime5 = time; 
  }
  if (buttonState6 == HIGH) {       
    buttonTime6 = time; 
  }
  
  // Create an array that tracks the most recent time a button has been pressed
  
  int timeArray[] = {buttonTime, buttonTime2, buttonTime3};
  int timeArray2[] = {buttonTime4, buttonTime5, buttonTime6};
  
  // Check for highest and lowest value in the array
  
  // A Button
  
  highest = timeArray[0];
  for (int i=0; i<3; i++) {
    if (timeArray[i]>=highest){
      highest = timeArray[i];
    }
  }
  
  lowest = timeArray[0];
  for (int i=0; i<3; i++) {
    if (timeArray[i]<=lowest){
      lowest = timeArray[i];
    }
  }
  
  middle = timeArray[0];
  for (int i=0; i<3; i++) {
    if ((timeArray[i]!=lowest) && (timeArray[i]!=highest)){
      middle = timeArray[i];
    }
  }
  
  if (abs(highest - lowest) <= interval) {
    Keyboard.press(buttonA);
    buttonTime = 0;
    buttonTime2 = 251;
    buttonTime3 = 502;
  } else if((abs(middle-lowest)<=interval) || (abs(middle-highest)<=interval)) {
    randNumber = random(5);
    if (randNumber == 1) {
      Keyboard.press(buttonA);
      buttonTime = 0;
      buttonTime2 = 251;
      buttonTime3 = 502;
    }
    randNumber = random(5);
    if (randNumber == 1) {
      Keyboard.release(buttonA);
    }
  } else if (buttonTime!=0 || buttonTime2!=251 || buttonTime3!=502){
      randNumber = random(10);
      if (randNumber == 1) {
        Keyboard.press(buttonA);
        buttonTime = 0;
        buttonTime2 = 251;
        buttonTime3 = 502;
      }
      randNumber = random(3);
      if (randNumber == 1) {
        Keyboard.release(buttonA);
      }
  } else {
    Keyboard.release(buttonA);
  }
  
  // B Button
  
  highest = timeArray2[0];
  for (int i=0; i<3; i++) {
    if (timeArray2[i]>=highest){
      highest = timeArray[i];
    }
  }
  
  lowest = timeArray2[0];
  for (int i=0; i<3; i++) {
    if (timeArray2[i]<=lowest){
      lowest = timeArray[i];
    }
  }
  
  middle = timeArray2[0];
  for (int i=0; i<3; i++) {
    if ((timeArray2[i]!=lowest) && (timeArray2[i]!=highest)){
      middle = timeArray2[i];
    }
  }
  
  if (abs(highest - lowest) <= interval) {
    Keyboard.press(buttonB);
    buttonTime4 = 0;
    buttonTime5 = 251;
    buttonTime6 = 502;
  } else if((abs(middle-lowest)<=interval) || (abs(middle-highest)<=interval)) {
    randNumber = random(5);
    if (randNumber == 1) {
      Keyboard.press(buttonB);
      buttonTime4 = 0;
      buttonTime5 = 251;
      buttonTime6 = 502;
    }
    randNumber = random(5);
    if (randNumber == 1) {
      Keyboard.release(buttonB);
    }
  } else if (buttonTime!=0 || buttonTime2!=251 || buttonTime3!=502){
      randNumber = random(10);
      if (randNumber == 1) {
        Keyboard.press(buttonB);
        buttonTime4 = 0;
        buttonTime5 = 251;
        buttonTime6 = 502;
      }
      randNumber = random(3);
      if (randNumber == 1) {
        Keyboard.release(buttonA);
      }
  } else {
    Keyboard.release(buttonB);
  }
  
  // Joysticks
  int joystickBag[3] = {0,0,0};
  
  
  int leftright[] = {joystick1x, value3, value5};
  int updown[] = {value2, value4, value6};
  
  /*
  for (i = 0; i < 3; i++ ) {
    float y = ( updown[i] / 512.0 ) - 1.0;
    float x = ( leftright[i] / 512.0 ) - 1.0;
    float angle = atan2( y, x );
    float magnitude = sqrt( y * y + x * x );
    if ( magnitude > 0.3 ) {
      joystickBag[i] = angleToOctant( angle );
    }
  }  
  */
  
  for (i=0;i<3;i++){
    if (updown[i]>=0 && updown[i]<=299) {
      joystickBag[i]=KEY_DOWN_ARROW;
    } else if (updown[i]>=701 && updown[i]<=1024) {
      joystickBag[i]=KEY_UP_ARROW;
    }
  }
  
  for (i=0;i<3;i++){
    if (leftright[i]>=0 && leftright[i]<=299) {
      joystickBag[i]=KEY_RIGHT_ARROMW
    } else if (leftright[i]>=701 && leftright[i]<=1024) {
      joystickBag[i]=KEY_LEFT_ARROW;
    }
  }
  
  randNumber = random(3);
  
  if (joystickBag[randNumber]==0) {
    Keyboard.release(previousStick);
  } else if (previousStick!=joystickBag[randNumber]){
    Keyboard.release(previousStick);
    Keyboard.press(joystickBag[randNumber]);
  }
  
  previousStick = joystickBag[randNumber];
}

int angleToOctant( float angle ) {
  //TODO
}
