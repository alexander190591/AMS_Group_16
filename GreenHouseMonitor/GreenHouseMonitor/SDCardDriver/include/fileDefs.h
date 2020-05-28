/** 
  *	
  *	
  *	@file:		./GreenHouseMonitor/SDCardDriver/fileDefs.h
  *	@date:		14-05-2020 13:10:28
  *	@author:	Tonni Lutze
  *
  *	@brief Struct containing doubles for air humidity, soil humidity and air temperature
  *	
  *	
  *	Major change #1:
  *	
**/



#ifndef FILEDEFS_H_
#define FILEDEFS_H_
#pragma once

typedef struct
{
	double	tempAir;
	double	humidityAir;
	double	humiditySoil;
	
}SensorDataObj;



#endif /* FILEDEFS_H_ */