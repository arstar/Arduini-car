// 
// 
// 
#include "Driver.h"

void DriverClass::init(VehicleClass car, uint8_t servoChannel, uint8_t servoPin, uint8_t echoPin, uint8_t triggerPin)
{
	sonar = new NewPing(triggerPin, echoPin, 200);
	this->car = car;
	servoTimer.init(100);
	sonarTimer.init(100);
	directionTimer.init(1500);
	steerTimer.init(1500);
	this->servoChannel = servoChannel;
	ledcSetup(servoChannel, freq, resolution);
	ledcAttachPin(servoPin, servoChannel);
	this->lookForward();
	increment = -15;
}

void DriverClass::moveHead(int position) {
	currentPosition = position;
	ledcWrite(servoChannel, (position*39.8222) + leftPosition);
}

void DriverClass::lookAround()
{
	if (sonarTimer.shouldRun()) {
		std::map<int, int>::iterator it = positions.find(currentPosition);
		if (it != positions.end()) {
			it->second = sonar->ping_cm();
		}
		else {
			positions.insert(std::make_pair(currentPosition,sonar->ping_cm()));
		}
	}

	if(servoTimer.shouldRun()){
		currentPosition += increment;
		this->moveHead(currentPosition);		
		if ((currentPosition >= 180) || (currentPosition <= 0)) // end of sweep
		{
			// reverse direction
			increment = -increment;
		}
	}
}

void DriverClass::lookLeft()
{
	moveHead(0);
}

void DriverClass::lookRight()
{
	moveHead(180);
}

void DriverClass::lookForward()
{
	moveHead(90);
}

void DriverClass::drive() {
	this->lookAround();
	//Lets determine the direction based on the most clearance
	//TODO I need to store the direction of the servo + the distance in an array an go throught that
	if(directionTimer.shouldRun()){
		auto dir = findBestDirection();

		
		Serial.print(dir.first);
		Serial.print("-");
		Serial.println(dir.second);
	}
	//Lets start driving
}

void DriverClass::steer(int direction, int distance) {
	if(steerTimer.shouldRun()){
		if(distance > 50){
			if (direction < 90) {
				car.left(30);
			}
			else if (direction > 90) {
				car.right(30);
			}
			else {
				car.throttleMax();
			}
		}
		else {
			//Stop and make 90 degree turn and see if we can continue
			car.brake();
			car.left(255);
			steerTimer.setInterval

		}
	}
}


std::pair<int, int> DriverClass::findBestDirection() {
	return *std::max_element(
		positions.begin(), 
		positions.end(),
		[] (const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
		return p1.second < p2.second; });
}


DriverClass Driver;

