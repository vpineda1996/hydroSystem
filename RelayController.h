#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Timer.h"
#include "ChangeStateButton.h"

#pragma once

#ifndef HEATER_PIN
#define HEATER_PIN 8
#endif

#ifndef WATER_PUMP_PIN
#define WATER_PUMP_PIN 7
#endif

#ifndef AIR_PUMP_PIN
#define AIR_PUMP_PIN 9
#endif

#ifndef OTHER_PIN
#define OTHER_PIN 10
#endif


enum RelayPin {
  Heater = HEATER_PIN, WaterPump = WATER_PUMP_PIN, AirPump = AIR_PUMP_PIN, Other = OTHER_PIN
};

typedef struct Relay {
  StateDescription& relayState;
  enum RelayPin pin;
  bool forceOnMode;
} Relay;

class RelayController {
  public:
  RelayController(int n, Relay* rs) : relays(rs), numOfRelays(n) {
    pinMode(RelayPin::Heater, OUTPUT);
    pinMode(RelayPin::WaterPump, OUTPUT);
    pinMode(RelayPin::AirPump, OUTPUT);
    pinMode(RelayPin::Other, OUTPUT);

    digitalWrite(RelayPin::Heater, HIGH);
    digitalWrite(RelayPin::WaterPump, HIGH);
    digitalWrite(RelayPin::AirPump, HIGH);
    digitalWrite(RelayPin::Other, HIGH);
    
  }
  void update();
  void setForceOn(bool);

  private:
  void normalUpdate();
  void forceOnUpdate();
  const struct Relay* relays;
  const uint8_t numOfRelays;
  bool forceOnActive;
};

