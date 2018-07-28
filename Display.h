
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Timer.h"
#include "State.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#pragma once

#ifndef LCD_I2C_ADDR
#define LCD_I2C_ADDR 0x3F
#endif


class Display {
  public:
  LiquidCrystal_I2C lcd;  
  Display(ABTimer&, ABTimer&, SensorBasedState&);

  void updateScreen();
  void init();

  private:
  SensorBasedState& temp;

  ABTimer& waterPumpTime;
  ABTimer& airPumpTime;
  
  bool needsUpdate;
  void drawPump(const char*, enum State, Timer&);
};

