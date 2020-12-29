/*************************************************************************
 * A1454 Hall Effect Wireling Test Code - 
 * This program will show the basic method of interfacing with the sensor 
 * by printing out the Analog values (readings from 0 to 4096 (12-bit)) on
 * the Serial Monitor.
 * 
 * Hardware by: TinyCircuits
 * Written by: Laveréna Wienclaw for TinyCircuits
 * 
 * Initiated: June 2019
 * Updated: Jan 2020
 ************************************************************************/
 
#include <Wire.h>               // For I2C communication
#include <Wireling.h>           // For Interfacing with Wirelings
#include "TinyCircuits_A1454.h" // For the sensor

// A sensor object, the methods will be used to interface with the A1454
TinyCircuits_A1454 hall = TinyCircuits_A1454();

// Make Serial Monitor compatible for all TinyCircuits processors
#if defined(ARDUINO_ARCH_AVR)
  #define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
  #define SerialMonitorInterface SerialUSB
#endif

void setup() {
  // Begin communication 
  SerialMonitorInterface.begin(9600);
  SerialMonitorInterface.println("HALL LIBRARY TEST CODE");
  Wire.begin();
  
  // Enable & Power Wireling
  Wireling.begin();
  Wireling.selectPort(0); // This must match the port the Wireling is connected to 
                          // on the Adapter board
  
  hall.begin();
//  hall.wake(); 
}

void loop() {
  long mag = hall.readMag();
  long temp = hall.readTemp();
  long mode = hall.readMode();

//  if (mode == 0) SerialMonitorInterface.print("AWAKE\t\t");
//  else if (mode == 1) SerialMonitorInterface.print("SLEEPING\t\t");

  SerialMonitorInterface.print("Mag: ");
  SerialMonitorInterface.print((float)mag / 4.0/ 10.0); // convert to ENOB, and Gauss to millitesla
  SerialMonitorInterface.print("mT"); // millitesla
  SerialMonitorInterface.print('\t');

  SerialMonitorInterface.print("TempF: ");
  int tempF = ((temp * 1.8) + 32);
  SerialMonitorInterface.print(tempF);
  SerialMonitorInterface.print("°F");
  SerialMonitorInterface.print('\t');

  SerialMonitorInterface.print("TempC: ");
  SerialMonitorInterface.print(temp);
  SerialMonitorInterface.println("°C");

  delay(500);
}
