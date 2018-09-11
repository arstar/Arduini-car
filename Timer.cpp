// 
// 
// 

#include "Timer.h"



TimerClass Timer;

void TimerClass::init(int updateInterval)
{
	this->updateInterval = updateInterval;
}

boolean TimerClass::shouldRun()
{
	if ((millis() - lastUpdate) > updateInterval) {
		lastUpdate = millis();
		return true;
	}
	return false;
}

void setInterval(int udpateInterval) {
	this->updateInterval = updateInterval;
}
