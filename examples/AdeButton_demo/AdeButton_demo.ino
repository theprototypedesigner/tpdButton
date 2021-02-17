#include "AdeButton.h"

// Declare each button. AdeButton name(pin,rest_state,pinMode);

// By default the rest state of the buttons is HIGH and the PinMode is INPUT_PULLUP
// which is a normally open button that uses the internal pullup resistor.
// If you want to use different settings just add the other parameters, for example:
// AdeButton button1(5,HIGH,INPUT);

AdeButton button1(5);
AdeButton button2(6);

void setup() {
  Serial.begin(9600);

  // The library has some defaul delays that can be changed:
  // button1.setDebounceDelay(time_in_milliseconds); by default 30
  // button1.setMultiPressDelay(time_in_milliseconds); by default 400
  // button1.setLongPressDelay(time_in_milliseconds); by default 2000
  
}

void loop() {
  // The update function for each button has to be in the loop,
  // this function is responsible of reading the buttons.
  button1.update();
  button2.update();

  // How to detect a single press
  if(button1.singlePress()) {
    Serial.println("Single press detected");
  }
  // How to detect a double press
  if(button1.doublePress()) {
    Serial.println("Double press detected");
  }
  // How to detect a long press
  if(button1.longPress()) {
    Serial.println("Long press detected");
  }

  // How to detect a multiple press, specify the number of presses you want to detect
  if(button1.multiPress(4)) {
    Serial.print("Multi press detected: ");
    Serial.println("4");
  }

  // How to detect when a button is pressed or not
  if(button2.isPressed()) {
    Serial.println("You are pressing button 2");
  }
  if(button2.isReleased()) {
    Serial.println("Button 2 has been released");
  }
}
