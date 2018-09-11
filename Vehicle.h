// Car.h

#ifndef _CAR_h
#define _CAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class VehicleClass
{
 protected:
	 int maxSpeed = 255;
	 int minSpeed = 190;
	 int currentSpeed = 0;
	 int powerRightPin;
	 int powerLeftPin;
	 int right1Pin;
	 int right2Pin;
	 int left1Pin;
	 int left2Pin;
	 int frontLightPin;
	 int backLightPin;
	 int brakeLightPin;
	 int leftBlinkerPin;
	 int rightBlinkerPin;
	 boolean brakeLight = false;
	 boolean frontLight = false;
	 boolean backLight = false;
	 boolean leftBlinker = false;
	 boolean rightBlinker = false;
	 int freq = 30000;
	 int resolution = 8;

 public:
	void init(
		uint8_t powerRightPin, uint8_t powerLeftPin, 
		uint8_t pwmChannelA, uint8_t pwmChannelB,
		uint8_t right1Pin, uint8_t right2Pin, 
		uint8_t left1Pin, uint8_t left2Pin
		);
	void brake();
	void throttleMax();
	void throttle(int speed);
	void throttle(int speed, int increments, int delay);
	void straighten();
	void reverseMax();
	void reverse(int speed);
	void left(int percentage);
	void right(int percentage);
	void toggleBrakeLight();
	void toggleFrontLight();
	void toggleBackLight();
	void toggleLeftBlinker();
	void toggleRightBlinker();
};

extern VehicleClass Vehicle;

#endif

