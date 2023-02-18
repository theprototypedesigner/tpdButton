/*
 * TpdButton.h - Simple intuitive Arduino library
 * to read different events on a single button.
 * 
 * Author: Ubaldo Andrea Desiato | theprototypedesigner
 * Created: 7 Feb 2021
 * Last update: 18 Feb 2023
 */

#ifndef TPD_BUTTON_H
#define TPD_BUTTON_H

#include "Arduino.h"

#define DEFAULT_DEBOUNCE_DELAY      30
#define DEFAULT_MULTI_PRESS_DELAY   400
#define DEFAULT_LONGPRESS_DELAY     2000

class TpdButton {

  private:
    byte _pin;    
    byte _restState;
    byte _lastReading;
    byte _buttonState;
    uint16_t _debounceDelay   = DEFAULT_DEBOUNCE_DELAY;
    uint16_t _multiPressDelay      = DEFAULT_MULTI_PRESS_DELAY;
    uint16_t _longPressDelay       = DEFAULT_LONGPRESS_DELAY;

    bool _longPress;
    bool _singlePress;
    bool _doublePress;
    bool _released;
    byte _multiPress;
  
    unsigned long _eventTime;
    unsigned long _lastDebounceTime;
    
    enum state_t { AWAIT_PRESS, DEBOUNCE_PRESS, AWAIT_RELEASE, DEBOUNCE_RELEASE, AWAIT_MULTI_PRESS } state;
    int _pressCount;

    void debounce();
    byte getState();
    int checkPress();
    

  public:

    TpdButton(uint8_t pin, uint8_t restState = LOW, uint8_t PinMode = INPUT);
  
    // Set attributes
    void setDebounceDelay(uint16_t value);
    void setMultiPressDelay(uint16_t value);
    void setLongPressDelay(uint16_t value);
    void update();
    bool isPressed();
    bool isReleased();
    bool singlePress();
    bool longPress();
    bool doublePress();
    bool multiPress(byte nOfPress);
 
};

#endif
