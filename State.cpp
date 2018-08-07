#include "State.h"

void Sensor::setValue(float v) {
  value = v;
}


void SensorBasedState::setValue(float v) {
  Sensor::setValue(v);
  if (value > minimum) {
     if (value <= threshold) {
      state = ENABLED;
    } else if (state == ENABLED && (threshold - value) <= tolerance) {
      state = ENABLED;
    } else {
      state = DISABLED;
    } 
  }
  changed = true;
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

