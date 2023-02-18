#include "TpdButton.h"

TpdButton::TpdButton(uint8_t pin, uint8_t restState, uint8_t PinMode)
{
  _pin = pin;
  _restState = restState;
  pinMode(_pin, PinMode);
  state = AWAIT_PRESS;
  buttonState = _restState;
}

//Set attributes
void TpdButton::setDebounceDelay(uint16_t value){_debounceDelay = value;}
void TpdButton::setMultiPressDelay(uint16_t value){_multiPressDelay = value;}
void TpdButton::setLongPressDelay(uint16_t value){_longPressDelay = value;}

void TpdButton::debounce() {
  byte newReading = digitalRead(_pin);

  if (newReading != lastReading)
  {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > _debounceDelay) // change variable
  {
    buttonState = newReading;
  }
  lastReading = newReading;
}

byte TpdButton::getState() {
  this->debounce();
  return buttonState;
}

int TpdButton::checkPress()
{
  if (state == AWAIT_PRESS) {
    _pressCount = 0;
    if (!(this->getState() == _restState)) {
      state = AWAIT_RELEASE;
      _eventTime = millis();  
    }  
  } 
  
  else if (state == AWAIT_RELEASE) {
    if (this->getState() == _restState) {
      _released = true;
      if ((millis() - _eventTime) > _longPressDelay) {
        state = AWAIT_PRESS;
        return -1;
      }
      _pressCount++;
      state = AWAIT_MULTI_PRESS;
      _eventTime = millis();
    }
  } 
  
  else {
    if (!(this->getState() == _restState)) {
      state = AWAIT_RELEASE;
      _eventTime = millis(); 
    } 
    else if ((millis() - _eventTime) > _multiPressDelay) {
      state = AWAIT_PRESS;
      return _pressCount;
    } 
  }
  return 0; 
}

void TpdButton::update() {
  int _status = this->checkPress();
  if(_status == -1) {
    _longPress = true;
  } else if (_status == 1) {
    _singlePress = true;
  } else if (_status == 2) {
    _doublePress = true;
  } else if(_status >2) {
    _multiPress = _status;
  }
}

bool TpdButton::isPressed() {
  return (!(this->getState() == _restState));
}

bool TpdButton::isReleased() {
  bool var = _released;
  _released = false;
  return (var);
}

bool TpdButton::singlePress() {
  bool var = _singlePress;
  _singlePress = false;
  return (var);
}

bool TpdButton::longPress() {
    bool var = _longPress;
  _longPress = false;
  return (var);
}

bool TpdButton::doublePress() {
    bool var = _doublePress;
  _doublePress = false;
  return (var);
}

bool TpdButton::multiPress(byte nOfPress) {
    int var = _multiPress;
  _multiPress = 0;
  return (var==nOfPress);
}
