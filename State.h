#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#pragma once

enum State { ENABLED, DISABLED };

class StateDescription {
   public:
   StateDescription() : state(DISABLED) {};
   StateDescription(enum State s): state(s) {};
   enum State state;
};

class Sensor {
  public:
  virtual void setValue(float);
  float getValue() { return value; }
  
  protected:
  float value;
};

class SensorBasedState : public StateDescription, public Sensor  {
  public:
  SensorBasedState(float t): SensorBasedState(t, State::DISABLED) {};
  SensorBasedState(float t, enum State s): SensorBasedState(t, 0, -1, s) {};
  SensorBasedState(float th, float tol, float mi): SensorBasedState(th, tol, mi, State::DISABLED) {};
  SensorBasedState(float th, float tol, float mi, enum State s): threshold(th), tolerance(tol), minimum(mi), changed(false), StateDescription(s), Sensor() {};
  void setValue(float);
  bool hasChanged();
  
  private: 
  bool changed;
  const float tolerance;
  const float minimum;
  const float threshold;
};

