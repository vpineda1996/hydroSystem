#include "RelayController.h"

void RelayController::forceOnUpdate() {
  int i = 0;
  while (i != numOfRelays) {
    if (relays[i].forceOnMode) {
      digitalWrite(relays[i].pin, LOW);
    } else {
      digitalWrite(relays[i].pin, HIGH);
    }
    i++;
  }
}

void RelayController::normalUpdate() {
  int i = 0;
  while (i != numOfRelays) {
    if (relays[i].relayState.state == ENABLED) {
      digitalWrite(relays[i].pin, LOW);
    } else {
      digitalWrite(relays[i].pin, HIGH);
    }
    i++;
  }
}

void RelayController::update() {
  if (forceOnActive) {
    forceOnUpdate();
  } else {
    normalUpdate();
  }
}

void RelayController::setForceOn(bool a) {
  forceOnActive = a;
}

