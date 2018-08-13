#include "State.h"

void Sensor::setValue(float v) {
  value = v;
}


void SensorBasedState::setValue(float v) {
  if (v > minimum) {
    Sensor::setValue(v);
    if (value <= threshold) {
      state = ENABLED;
    } else if (state == ENABLED && (value - threshold) <= tolerance) {
      state = ENABLED;
    } else {
      state = DISABLED;
    } 
    changed = true;
  }
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

