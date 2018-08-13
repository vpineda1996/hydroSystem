# hydroSystem
Arduino automation of pump &amp; temp control for NFT hydroponic system

### Run & Install
This was built and created to run indefinitely on any Arduino platform. The program 
is about 10k big and should remain about the same to mantain compatibility.

Use the Arduino IDE to compile, you will need to three libraries
- [OneWire](https://github.com/PaulStoffregen/OneWire)
- [Maxim Temperature Library](https://github.com/milesburton/Arduino-Temperature-Control-Library)
- [New LiquidCrystal](https://bitbucket.org/fmalpartida/new-liquidcrystal/)

### Default pins
There are 4 default pins for relays documented in RelayController:

| Name | Pin Number |
| ---- | -----------|
| WATER_PUMP_PIN | 7 |
|OTHER_PIN | 8 |
|AIR_PUMP_PIN | 9 |
|HEATER_PIN |10 |

You can overwrite them by setting -D flags on the compiler or modifying them by hand.
