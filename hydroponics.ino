#include <Wire.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

#include "RelayController.h"
#include "Display.h"
#include "Timer.h"

Timer onWpt ( 0, 20, 0 );
Timer offWpt ( 0, 20, 0 );

Timer onAir ( 0, 15, 0 );
Timer offAir ( 0, 5, 0 );

ABTimer waterT (onWpt, offWpt);
ABTimer airT (onAir, offAir);

GlobalClock globalClock;

SensorBasedState sbs(19.0);

Display d(waterT, airT, sbs);

Relay relays[] = {{waterT ,RelayPin::WaterPump}, {airT, RelayPin::AirPump}, {sbs, RelayPin::Heater}};
RelayController rc(3, relays);

/**
 * ( SIMPLE DEFINITIONS FOR PINS )
 * The address is fixed for the lcd screen
 */
#define LCD_I2C_ADDR 0x3F

#define TEMP_SENSOR_PIN 2
#define WATER_PUMP_PIN 7
#define AIR_PUMP_PIN 9

/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(TEMP_SENSOR_PIN); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 

void setup()  
{
  d.init();            // Clear the LCD screen
  sensors.begin();     // Setup sensors
  globalClock.subscribe(&waterT);
  globalClock.subscribe(&airT);
}

unsigned long time;
void loop()   
{
    /**
     * On every loop we will update the screen, wait 1 second
     * and then update the values
     */
    d.updateScreen();
    // sensors.requestTemperatures(); // Send the command to get temperature readings 
    delay(max(1000 - time, 1)); 

    time = millis();
    // make world tick
    globalClock.tick();

    // update temp
    sbs.setValue(sensors.getTempCByIndex(0));

    // updates the relay states
    rc.update();
    time -= millis();
}
