#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "State.h"
#pragma once

#define NUM_GLOBAL_CLOCK 5

class Timer {
  public:
  Timer(uint8_t h, uint8_t m, uint8_t s) : hr(h), sec(s) {
    min = m;
  }
  uint8_t hr;
  uint8_t min;
  uint8_t sec;

  uint8_t reduceSecond();
  uint8_t reduceMinute();
  uint8_t reduceHour();
  void virtual tick();

};

class GlobalClock {
  public:
  GlobalClock() : n(0) {};
  void subscribe(Timer*);
  void unsubscribe(Timer*);
  void tick();

  private:
  uint8_t n;
  Timer* timers[NUM_GLOBAL_CLOCK];
};

/**
 * Main definition of a Timer that is used mostly everywhere where we tick!
 * It will automatically subscribe to global clock. If you want to make this
 * clock tick its better to use a global clock
 */
class ABTimer : public Timer, public StateDescription {
  public:
  ABTimer(Timer& on, Timer& off, enum State s);
  ABTimer(Timer& on, Timer& off);
  void tick();

  private:
  Timer& onTime;
  Timer& offTime;

};

inline bool operator==(const Timer& lhs, const Timer& rhs){
    return lhs.hr == rhs.hr && lhs.min == rhs.min && lhs.sec == rhs.sec;
}

inline bool operator!=(const Timer& lhs, const Timer& rhs){
    return !(lhs == rhs);
}

