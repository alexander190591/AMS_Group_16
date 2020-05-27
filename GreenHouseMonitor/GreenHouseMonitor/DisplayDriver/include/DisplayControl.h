/*
 * DisplayControl.h
 *
 * Created: 16-04-2020 09:46:15
 *  Author: Sebastian Folsach
 */ 


#ifndef DISPLAYCONTROL_H_
#define DISPLAYCONTROL_H_

//Functions for updating display with values,
//  reserved for non-touch


void updateWindowDisplay(char*);
void updateEarthHumidDisplay(char*);
void updateTemperaturDisplay(char*);


//The functions for calling main controldisplay parts,
//  reserved for touch
void windowControlDisplay(unsigned int, unsigned int);
void earthHumidControlDisplay(unsigned int, unsigned int);





#endif /* DISPLAYCONTROL_H_ */