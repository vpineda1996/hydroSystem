#include <OneWire.h> 
#include <DallasTemperature.h>

#include "RelayController.h"
#include "Display.h"
#include "Timer.h"
#include "ChangeStateButton.h"

/*******************************************************************/
// ( DEFINITIONS FOR PINS )
// LCD SCREEN
#define LCD_I2C_ADDR 0x3F
// Temperature sensor data pin
#define TEMP_SENSOR_PIN 2
// Button that forces the pump to turn on
#define FORCE_ON_BUTTON 3
// Pump buttons
#define WATER_PUMP_PIN 7
#define AIR_PUMP_PIN 9
/********************************************************************/

/********************************************************************/
// ( PIN INSTANTIATION )
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(TEMP_SENSOR_PIN); 
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 


Timer onWpt ( 0, 20, 0 );
Timer offWpt ( 0, 20, 0 );

Timer onAir ( 0, 15, 0 );
Timer offAir ( 0, 5, 0 );

ABTimer waterT (onWpt, offWpt);
ABTimer airT (onAir, offAir);

GlobalClock globalClock;

SensorBasedState sbs(19.0, 1.0, -100.0);
ChangeStateButton forceOnBtn(FORCE_ON_BUTTON);

Display d(waterT, airT, sbs);

Relay relays[] = {{waterT ,RelayPin::WaterPump, true}, {airT, RelayPin::AirPump, true}, {sbs, RelayPin::Heater, false}};
RelayController rc(3, relays);

void setup()  
{
  d.init();            // Clear the LCD screen
  sensors.begin();     // Setup sensors
  globalClock.subscribe(&waterT);
  globalClock.subscribe(&airT);
}

#define TEMP_CYCLE (1 << 7)
#define BTN_CYCLE_READ (1 << 3)
#define TIME_CYCLE ( 1 << 2 )
#define CYCLE(c,t) !(c % t)

#define MILLIS_IN_SEC 1000
#define HALF_SEC_MILLIS (MILLIS_IN_SEC / 2)

void onSecond() {
  // make world tick
  globalClock.tick();
  // update relays
  rc.update();
}

void halfSecond() {
  // update the screen
  d.updateScreen();
}

void timeUpdater() {
  static unsigned long timer = millis(), secondsOffset = 0, halfOffset = 0;
  unsigned long currentTime = millis();
  #define INTERVAL(interval, offset) (currentTime - timer) - offset >= interval

  // second
  if (INTERVAL(MILLIS_IN_SEC, secondsOffset)) {
     onSecond();
     secondsOffset += MILLIS_IN_SEC;
     
  }
  
  // half-second
  if (INTERVAL(HALF_SEC_MILLIS, halfOffset)) {
     halfSecond();
     halfOffset += HALF_SEC_MILLIS;
  }
}

void cycleUpdater() {
  static unsigned int cycles = 0;

  // update temp
  if (CYCLE(cycles, TEMP_CYCLE)) {
    sensors.requestTemperatures();
    sbs.setValue(sensors.getTempCByIndex(0));
  }


  // check force on button, if active activate all relays
  if (CYCLE(cycles, BTN_CYCLE_READ)) { 
    if (forceOnBtn.active()) {
      rc.setForceOn(true);
      d.setForceOn(true);
    } else {
      rc.setForceOn(false);
      d.setForceOn(false);
    } 
  }

  // tick time
  if (CYCLE(cycles, TIME_CYCLE)) {
    timeUpdater();
  }
  cycles++;
}

void loop()   
{
  cycleUpdater();
  delay(50);
}
