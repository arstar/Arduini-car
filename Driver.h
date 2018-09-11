// Driver.h
#include <map>
#include <iterator>
#include <algorithm>
#include "Timer.h"
#include <NewPing.h>
#include "Vehicle.h"
#ifndef _DRIVER_h
#define _DRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class DriverClass
{
 protected:
	 int freq = 50;
	 int resolution = 16;
	 int leftPosition = 1024;
	 int centerPosition = 5000;
	 int rightPosition = 8192;
	 int currentPosition;
	 int increment = 1;
	 uint8_t servoChannel;
	 uint8_t servoPin;
	 TimerClass servoTimer;
	 TimerClass sonarTimer;
	 TimerClass directionTimer;
	 TimerClass steerTimer;
	 VehicleClass car;
	 std::multimap<int, int> positions;

 public:
	NewPing *sonar;
	void init(VehicleClass car, uint8_t servoChannel, uint8_t servoPin, uint8_t echoPin, uint8_t triggerPin);
	void moveHead(int position);
	void lookAround();
	void lookLeft();
	void lookRight();
	void lookForward();
	void drive();

	void steer(int direction, int distance);

	std::pair<int, int> findBestDirection();

};

extern DriverClass Driver;

#endif

