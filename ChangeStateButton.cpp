#include "ChangeStateButton.h"

ChangeStateButton::ChangeStateButton(int p) : pin(p) {
  pinMode(pin, INPUT);
  onState = !digitalRead(pin);
}

bool ChangeStateButton::active() {
  return digitalRead(pin) == onState;
}

