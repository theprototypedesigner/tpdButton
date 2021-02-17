#ifndef ADE_BUTTON_H
#define ADE_BUTTON_H

#include "Arduino.h"

#define DEFAULT_DEBOUNCE_DELAY      30
#define DEFAULT_MULTI_PRESS_DELAY   400
#define DEFAULT_LONGPRESS_DELAY     2000

class AdeButton {

  private:
    byte _pin;    
    byte _restState;
    byte lastReading;
    byte buttonState;
    uint16_t _debounceDelay   = DEFAULT_DEBOUNCE_DELAY;
    uint16_t _multiPressDelay      = DEFAULT_MULTI_PRESS_DELAY;
    uint16_t _longPressDelay       = DEFAULT_LONGPRESS_DELAY;

    bool _longPress;
    bool _singlePress;
    bool _doublePress;
    byte _multiPress;
  
    // State variables 
    unsigned long _eventTime;
    unsigned long lastDebounceTime;
    
    enum state_t { AWAIT_PRESS, DEBOUNCE_PRESS, AWAIT_RELEASE, DEBOUNCE_RELEASE, AWAIT_MULTI_PRESS } state;
    int _pressCount;

    void debounce();
    byte getState();
    int checkPress();
    

  public:

    AdeButton(uint8_t pin, uint8_t restState = HIGH, uint8_t PinMode = INPUT_PULLUP);
  
    // Set attributes
    void setDebounceDelay(uint16_t value);
    void setMultiPressDelay(uint16_t value);
    void setLongPressDelay(uint16_t value);
    void update();
    bool isPressed();
    bool singlePress();
    bool longPress();
    bool doublePress();
    bool multiPress(byte nOfPress);
 
    // status, number of clicks since last update
    // -1 = button held, 0 = button up, 1, 2, ... number of times button clicked
};

#endif
