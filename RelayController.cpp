#include "RelayController.h"

void RelayController::update() {
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

