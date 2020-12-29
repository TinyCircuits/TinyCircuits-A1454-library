//*******************************************************************
// TinyCircuits - A1454 Allegro Linear Hall-Effect Sensor Library 
// Written by: Brandon Farmer for TinyCircuits 
//
// Initiated: Wed. 8/ 8/2017 @  2:30PM 
//   Updated: Mon. 8/28/2017 @  7:15PM 
//
// Revision 0 - Original Release
//	RELEASED: 12/29/2020
//
//*******************************************************************

#include <avr/pgmspace.h>
#include <stdlib.h> 
#include <Arduino.h> 
#include <Wire.h> 
#include "TinyCircuits_A1454.h"

//Constructor 
TinyCircuits_A1454::TinyCircuits_A1454() {
  //Nothing Here 
}

//Begins I2C Communication
void TinyCircuits_A1454::begin() {
	Wire.begin();
	access(); 
	wake();  
}

//Read the 12-bit signed Magnetic Field Value 						
int16_t TinyCircuits_A1454::readMag() { 
	int16_t x; int16_t y; 
	
	Wire.beginTransmission(A1454_ADDRESS); 				
	Wire.write(A1454_OUTPUT); 								
	Wire.endTransmission(); 								
	
	Wire.requestFrom(A1454_ADDRESS, 4);						
	Wire.read(); 
	Wire.read();
	x = Wire.read();
	y = Wire.read(); 
	
	x <<= 8; 
		
	y |= x; 
	return y; 												
}

//Read the 12-bit signed Junction Temperature Value 
int16_t TinyCircuits_A1454::readTemp() {
	int16_t x; int16_t y; 
	
	Wire.beginTransmission(A1454_ADDRESS); 					
	Wire.write(A1454_TEMPOUT); 								
	Wire.endTransmission(); 								
	
	Wire.requestFrom(A1454_ADDRESS, 4);						
	Wire.read(); 
	Wire.read(); 
	x = Wire.read();
	y = Wire.read(); 
	
	x <<= 8; 
		
	y |= x; 
	y /= 8; 
	y += 25; 
	return y; 												
}

//Put the sensor into sleep mode 
void TinyCircuits_A1454::sleep(void) {
	Wire.beginTransmission(A1454_ADDRESS); 					
	Wire.write(A1454_SLEEP); 	
	Wire.write(0x00); 
	Wire.write(0x00);
	Wire.write(0x00); 
	Wire.write(0x01); 
	Wire.endTransmission(); 																				
}

//Wake the sensor from sleep mode, wait for it to stabilize 
void TinyCircuits_A1454::wake(void) {
	Wire.beginTransmission(A1454_ADDRESS); 					
	Wire.write(A1454_SLEEP); 	
	Wire.write(0x00); 
	Wire.write(0x00); 
	Wire.write(0x00); 
	Wire.write(0x00);
	Wire.endTransmission();
	//delay(1); 
}

//Check awake or sleep status 
uint8_t TinyCircuits_A1454::readMode(void) {
	Wire.beginTransmission(A1454_ADDRESS); 					
	Wire.write(A1454_SLEEP); 								
	Wire.endTransmission(); 								
	
	Wire.requestFrom(A1454_ADDRESS, 4);						
	Wire.read(); 
	Wire.read(); 
	Wire.read();
	
	return Wire.read(); 											
}

//Write ACCESS codes to write to allow write to registers? 
void TinyCircuits_A1454::access(void) {
	Wire.beginTransmission(A1454_ADDRESS); 
	Wire.write(A1454_ACCESS_ADDRESS); 
	Wire.write(A1454_ACCESS_CODE); 
	Wire.endTransmission(); 
}

















