// 
// 
// 

#include "Vehicle.h"

void VehicleClass::init(
	uint8_t EnableAPin, uint8_t EnableBPin,
	uint8_t pwmChannelA, uint8_t pwmChannelB,
	uint8_t right1Pin, uint8_t right2Pin,
	uint8_t left1Pin, uint8_t left2Pin
)
{
	this->right1Pin = right1Pin;
	this->right2Pin = right2Pin;
	this->left1Pin = left1Pin;
	this->left2Pin = left2Pin;
	this->powerRightPin = pwmChannelA;
	this->powerLeftPin = pwmChannelB;

	pinMode(EnableAPin, OUTPUT);
	pinMode(EnableBPin, OUTPUT);
	pinMode(right1Pin, OUTPUT);
	pinMode(right2Pin, OUTPUT);
	pinMode(left1Pin, OUTPUT);
	pinMode(left2Pin, OUTPUT);
	const int freq = 30000;
	const int resolution = 8;
	ledcSetup(powerRightPin, freq, resolution);
	ledcSetup(powerLeftPin, freq, resolution);
	ledcAttachPin(EnableAPin, pwmChannelA);
	ledcAttachPin(EnableBPin, pwmChannelB);

}

void VehicleClass::brake()
{
	//Stop all motors
	digitalWrite(right1Pin, LOW);
	digitalWrite(right2Pin, LOW);
	digitalWrite(left1Pin, LOW);
	digitalWrite(left2Pin, LOW);
}

void VehicleClass::throttleMax() {
	throttle(maxSpeed);
}


void VehicleClass::throttle(int speed)
{
	digitalWrite(right1Pin, LOW);
	digitalWrite(right2Pin, HIGH);
	digitalWrite(left1Pin, LOW);
	digitalWrite(left2Pin, HIGH);

	if (speed > maxSpeed) {
		speed = maxSpeed;
	}
	currentSpeed = speed;
	ledcWrite(powerRightPin, speed);
	ledcWrite(powerLeftPin, speed);
}

void VehicleClass::throttle(int speed, int increments, int wait)
{
	digitalWrite(right1Pin, LOW);
	digitalWrite(right2Pin, HIGH);
	digitalWrite(left1Pin, LOW);
	digitalWrite(left2Pin, HIGH);

	if (speed > maxSpeed) {
		speed = maxSpeed;
	}
	currentSpeed = speed;
	while (currentSpeed <= speed) {
		ledcWrite(powerRightPin, currentSpeed);
		ledcWrite(powerLeftPin, currentSpeed);
		currentSpeed = currentSpeed + increments;
		delay(wait);
	}
}

void VehicleClass::straighten()
{
	ledcWrite(powerRightPin, currentSpeed);
	ledcWrite(powerLeftPin, currentSpeed);
}

void VehicleClass::reverseMax()
{
	reverse(maxSpeed);
}

void VehicleClass::reverse(int speed)
{
	digitalWrite(right1Pin, HIGH);
	digitalWrite(right2Pin, LOW);
	digitalWrite(left1Pin, HIGH);
	digitalWrite(left2Pin, LOW);

	if (speed > maxSpeed) {
		//speed = maxSpeed;
	}
	currentSpeed = speed;
	ledcWrite(powerRightPin, speed);
	ledcWrite(powerLeftPin, speed);
}

void VehicleClass::left(int turningSpeed)
{

	int rightSpeed = currentSpeed;
	int leftSpeed = currentSpeed;
	if ((currentSpeed + turningSpeed) > maxSpeed) {
		leftSpeed = leftSpeed - turningSpeed;
	}
	else {
		rightSpeed = rightSpeed + turningSpeed;
	}

	ledcWrite(powerRightPin, rightSpeed);
	ledcWrite(powerLeftPin, leftSpeed);
}

void VehicleClass::right(int turningSpeed)
{
	int rightSpeed = currentSpeed;
	int leftSpeed = currentSpeed;
	if ((currentSpeed + turningSpeed) > maxSpeed) {
		rightSpeed = rightSpeed - turningSpeed;
	}
	else {
		leftSpeed = leftSpeed + turningSpeed;
	}
	ledcWrite(powerRightPin, rightSpeed);
	ledcWrite(powerLeftPin, leftSpeed);
}


void VehicleClass::toggleBrakeLight()
{
	if (brakeLight) {
		digitalWrite(brakeLightPin, LOW);
		brakeLight = false;
	}
	else {
		digitalWrite(brakeLightPin, HIGH);
		brakeLight = true;
	}
}

void VehicleClass::toggleFrontLight()
{
	if (frontLight) {
		digitalWrite(frontLightPin, LOW);
		frontLight = false;
	}
	else {
		digitalWrite(frontLightPin, HIGH);
		frontLight = true;
	}
}

void VehicleClass::toggleBackLight()
{
	if (backLight) {
		digitalWrite(backLightPin, LOW);
		backLight = false;
	}
	else {
		digitalWrite(backLightPin, HIGH);
		backLight = true;
	}
}

void VehicleClass::toggleLeftBlinker()
{
	if (leftBlinker) {
		digitalWrite(leftBlinkerPin, LOW);
		leftBlinker = false;
	}
	else {
		digitalWrite(leftBlinkerPin, HIGH);
		leftBlinker = true;
	}
}

void VehicleClass::toggleRightBlinker()
{
	if (rightBlinker) {
		digitalWrite(rightBlinkerPin, LOW);
		rightBlinker = false;
	}
	else {
		digitalWrite(rightBlinkerPin, HIGH);
		rightBlinker = true;
	}
}

VehicleClass Car;