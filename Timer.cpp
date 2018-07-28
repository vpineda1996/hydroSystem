#include "Timer.h"

ABTimer::ABTimer(Timer& on, Timer& off, enum State s) : onTime(on), offTime(off), StateDescription(s), Timer(off.hr, off.min, off.sec)  {
  if (s == ENABLED) {
    Timer& curT = on;
    hr = curT.hr;
    min = curT.min;
    sec = curT.sec;
  }
}
ABTimer::ABTimer(Timer& on, Timer& off) : onTime(on), offTime(off), StateDescription(State::DISABLED), Timer(off.hr, off.min, off.sec) {
}

uint8_t Timer::reduceMinute() {
  if (min <= 0) {
    if (reduceHour()) {
      min = 59;
    } else {
      return 0;
    }  
  } else {
    min--;
  }
  return 1;
}

uint8_t Timer::reduceHour() {
  if (hr <= 0) {
    return 0;
  } else {
    hr--;
    return 1;
  }
}

uint8_t Timer::reduceSecond() {
  if (sec <= 0) {
    if (reduceMinute()) {
      sec = 59;
    } else {
      return 0;
    }  
  } else {
    sec--;
  }
  return 1;
}

void Timer::tick() {
  reduceSecond();
}

void ABTimer::tick() {
  if(!reduceSecond()) {
    // Countdown reached zero!
    // Change the timer & state accordingly
    if (state == ENABLED) {
      hr = offTime.hr;
      min = offTime.min;
      sec = offTime.sec;
      state = DISABLED;
    } else {
      hr = onTime.hr;
      min = onTime.min;
      sec = onTime.sec;
      state = ENABLED;
    }
  }
}

void GlobalClock::subscribe(Timer* t) {
  if(n < 10) {
    timers[n] = t;
    n++;
  } else {
    for (int i = 0; i < n; i++) {
      if (!timers[i]) timers[i] = t;
    }
  }
}

void GlobalClock::unsubscribe(Timer* t) {
  for (int i = 0; i < n; i++) {
    timers[i] = NULL;
  }
}

void GlobalClock::tick() {
  for (int i = 0; i < n; i++) {
    if (timers[i]) timers[i]->tick();
  }
}



