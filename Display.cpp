#include "Display.h"

#define TEMP_LINE 0
#define WATER_PUMP_LINE 1
#define AIR_PUMP_LINE 2

#define ROLLER_SPACING 2

Display::Display(ABTimer& wpt, ABTimer& apt, SensorBasedState& sbs) : lcd(LCD_I2C_ADDR, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE), 
  waterPumpTime(wpt), 
  airPumpTime(apt), 
  temp(sbs),
  needsUpdate(true) {}

void Display::init() {
  lcd.begin(20,4);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight(); // finish with backlight on  
  lcd.clear();
}

void Display::setForceOn(bool a) {
  // ask for a refresh everytime that we force on
  if (forceOnActive != a) {
    needsUpdate = true;
  }
  forceOnActive = a;
}

void Display::drawPump(const char *name, enum State st, Timer& t) {
  lcd.print(name);
  lcd.print(st == State::ENABLED ? " ON" : " OFF");
  lcd.print(" : ");
  lcd.print(st == State::ENABLED ? " " : "");
  if (t.hr != 0) {
    lcd.print(t.hr);
    lcd.print("h");
  } else {
    lcd.print("  ");
  }
  if (t.min != 0 || t.hr != 0) {
    if (t.min < 10) lcd.print(" ");
    lcd.print(t.min);
    lcd.print("m");
  } else {
    lcd.print("   ");
  }
  
  if (t.sec < 10) lcd.print(" ");
  lcd.print(t.sec);
  lcd.print("s");
}

char states[] = {'|', '-'};

char getRolling(uint8_t state) {
  return states[state % (sizeof(states)/ sizeof(states[0]))];
}

void Display::updateScreen() {
  static uint8_t rollerState = 0;

  if (needsUpdate) {
     lcd.clear();

     // First draw temp
     lcd.setCursor(0, TEMP_LINE);
     lcd.print("Temp is: ");
     lcd.print(temp.getValue());
     lcd.print(" C");

     // if forced active, do not show timers
     if(forceOnActive) {
      lcd.setCursor(0, 2);
      lcd.print("Force On Mode Active");
      lcd.setCursor(0, 3);
      lcd.print("Press btn to disable");
      return;
     }

     needsUpdate = false;
  }

  // Draw water pump state
  lcd.setCursor(ROLLER_SPACING, WATER_PUMP_LINE); // Leave ROLLER_SPACING spaces to make the rotating effect work
  drawPump("Wtr", waterPumpTime.state, waterPumpTime);
  
  // Draw air pump state
  lcd.setCursor(ROLLER_SPACING, AIR_PUMP_LINE); // Leave ROLLER_SPACING spaces to make the rotating effect work
  drawPump("Air", airPumpTime.state, airPumpTime);
  
  // Then draw interactive liny
  if (waterPumpTime.state == State::ENABLED) {
    lcd.setCursor(0, WATER_PUMP_LINE);
    lcd.print(getRolling(rollerState));
  }

  if (airPumpTime.state == State::ENABLED) {
    lcd.setCursor(0,AIR_PUMP_LINE);
    lcd.print(getRolling(rollerState));
  }

  rollerState++; // increment the roller state so that we get a new one when we refresh!
}

