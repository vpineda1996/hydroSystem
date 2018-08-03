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
  SensorBasedState(float t): threshold(t), changed(false), StateDescription(), Sensor() {};
  SensorBasedState(float t, enum State s): threshold(t), changed(false), StateDescription(s), Sensor() {};
  void setValue(float);
  bool hasChanged();
  
  private: 
  bool changed;
  float threshold;
};

