#include "State.h"

void Sensor::setValue(float v) {
  value = v;
}


void SensorBasedState::setValue(float v) {
  Sensor::setValue(v);
  enum State newState = state;
  if (value <= threshold) {
    newState = ENABLED;
  } else {
    newState = DISABLED;
  }

  changed = newState != state;
  state = newState;
}

/**
 * Will say yes to the first caller who wants to know whether the state of the sensor has changed.
 */
bool SensorBasedState::hasChanged() {
  if (changed) {
    changed = false;
    return true;
  }
  return false;
}

