/*
 * DisplayControl.h
 *
 * Created: 16-04-2020 09:46:15
 *  Author: Sebastian Folsach
 */ 


#ifndef DISPLAYCONTROL_H_
#define DISPLAYCONTROL_H_

#include "TFTdriver.h"


/**
  * @brief Initiates Display Control driver.
  * 
  * 
  * @param void.
  * 
  * @return void
  * 
**/
void DisplayControlConstruct();



/**
  * @brief Makes outline for areas with touch functionality.
  * 
  * 
  * @param void.
  * 
  * @return void
  * 
**/
void writeWindowBoxes();

/**
  * @brief Writes to area designated for soil moisture.
  * 
  * 
  * @param Double which is the value to be written.
  * 
  * @return void
  * 
**/
void updateEarthHumidDisplay(double);

/**
  * @brief Writes to area designated for temperature.
  * 
  * 
  * @param Double which is the value to be written.
  * 
  * @return void
  * 
**/
void updateTemperaturDisplay(double);

/**
  * @brief Writes to area designated for air humidity.
  * 
  * 
  * @param Double which is the value to be written.
  * 
  * @return void
  * 
**/
void updateAirHumidDisplay(double);







#endif /* DISPLAYCONTROL_H_ */