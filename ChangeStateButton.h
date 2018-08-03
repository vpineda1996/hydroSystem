#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#pragma once

class ChangeStateButton {
  public:
  ChangeStateButton(int);
  bool active();
  
  private:
  const uint8_t pin;
  bool onState;
};

