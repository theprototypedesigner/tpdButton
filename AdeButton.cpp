#include "AdeButton.h"

AdeButton::AdeButton(uint8_t pin, uint8_t restState, uint8_t PinMode)
{
  _pin = pin;
  _restState = restState;
  pinMode(_pin, PinMode);
  state = AWAIT_PRESS;
  buttonState = _restState;
}

//Set attributes
void AdeButton::setDebounceDelay(uint16_t value){_debounceDelay = value;}
void AdeButton::setMultiPressDelay(uint16_t value){_multiPressDelay = value;}
void AdeButton::setLongPressDelay(uint16_t value){_longPressDelay = value;}

void AdeButton::debounce() {
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

byte AdeButton::getState() {
  this->debounce();
  return buttonState;
}

int AdeButton::checkPress()
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

void AdeButton::update() {
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

bool AdeButton::isPressed() {
  return (!(this->getState() == _restState));
}

bool AdeButton::isReleased() {
  bool var = _released;
  _released = false;
  return (var);
}

bool AdeButton::singlePress() {
  bool var = _singlePress;
  _singlePress = false;
  return (var);
}

bool AdeButton::longPress() {
    bool var = _longPress;
  _longPress = false;
  return (var);
}

bool AdeButton::doublePress() {
    bool var = _doublePress;
  _doublePress = false;
  return (var);
}

bool AdeButton::multiPress(byte nOfPress) {
    int var = _multiPress;
  _multiPress = 0;
  return (var==nOfPress);
}
