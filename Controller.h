// Controller.h
#include "Timer.h"
#include "Vehicle.h"
#ifndef _CONTROLLER_h
#define _CONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ControllerClass
{
 protected:
	 TimerClass controllerTimer;
 public:
	void init(String name);
	void handleInput(VehicleClass car);
};

extern ControllerClass Controller;

#endif

