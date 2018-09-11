// Timer.h

#ifndef _TIMER_h
#define _TIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class TimerClass
{
 protected:
	 int  updateInterval;      // interval between updates
	 unsigned long lastUpdate; // last update of position

 public:
	void init(int updateInterval);
	void setInterval(int updateInterval);
	boolean shouldRun();
};

extern TimerClass Timer;

#endif

