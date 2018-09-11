#include "Controller.h"
#include "Driver.h"
#include "Vehicle.h"
#include "esp32-hal-ledc.h"


#define MOTOR_ENA 26
#define MOTOR_ENB 25
#define MOTOR_IN1 12
#define MOTOR_IN2 13
#define MOTOR_IN3 16
#define MOTOR_IN4 17
#define PWM_CHANNEL_A 0
#define PWM_CHANNEL_B 1
#define SERVO_CHANNEL 2
#define SERVO_PIN 27
#define ECHO_PIN 5
#define TRIGGER_PIN 23


VehicleClass car;
DriverClass driver;
ControllerClass controller;


void setup() {
	//pinMode(OBSTOCALE_PIN, INPUT);

	car.init(MOTOR_ENA, MOTOR_ENB, PWM_CHANNEL_A, PWM_CHANNEL_B, MOTOR_IN1, MOTOR_IN2, MOTOR_IN3, MOTOR_IN4);
	driver.init(car, SERVO_CHANNEL, SERVO_PIN, ECHO_PIN, TRIGGER_PIN);
	controller.init("Arie's car");
	Serial.begin(115200);
	Serial.println();
	//test();
	
}

void test() {
	car.throttleMax();
	delay(10000);
	car.left(50);
	delay(10000);
	car.right(50);
	delay(10000);
	car.throttle(100);
	delay(10000);
	car.left(10);
	delay(10000);
	car.throttle(100);
	delay(10000);
	car.right(10);
}

void loop() {
	//	test();
	//controller.handleInput(car);
	driver.drive();
}

