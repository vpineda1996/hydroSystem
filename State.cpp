#include "State.h"

void Sensor::setValue(float v) {
  value = v;
}


void SensorBasedState::setValue(float v) {
  Sensor::setValue(v);
  if (value < threshold) {
    state = ENABLED;
  } else {
    state = DISABLED;
  }
}

