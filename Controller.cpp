// 
// 
// 

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#include "Controller.h"
BluetoothSerial SerialBT;

void ControllerClass::init(String name)
{
	SerialBT.begin(name); //Bluetooth device name
	controllerTimer.init(10);
}

void ControllerClass::handleInput(VehicleClass car)
{
	if(!controllerTimer.shouldRun()){
		return;
	}
	if (Serial.available()) {
		SerialBT.write(Serial.read());
	}
	char code;
	String value = "";
	while (SerialBT.available()) {

		char inputChar = SerialBT.read();
		String input = (String)inputChar;
		Serial.write(inputChar);
		for (int i = 0; i < input.length(); i++) {
			int c = input[i];
			if (isDigit(c)) {
				value += (char)c;
			}
			else if (c != '\n') {
				code = c;
			}
			else {
				break;
			}
		}
		switch (code) {

			case 'F'://N 
				car.throttleMax();
				break;
			case 'E': //NE
				car.throttleMax();
				car.right(100);
				break;
			case 'Q': //NW
				car.throttleMax();
				car.left(100);
				break;
			case 'L': //W
				car.left(255); 
				break;
			case 'G':  //S
				car.reverseMax();
				break;
			case 'Z': //SW
				car.reverseMax();
				car.left(100);   
				break;
			case 'C': 
				car.reverseMax();
				car.right(255); 
				break;
			case 'R': car.right(100);   break;
			case 'S': car.brake();     break;
				/*
			case 'M': turnOnLight(FRONT_LED_PIN); break;
			case 'm': turnOffLight(FRONT_LED_PIN); break;
			case 'N': turnOnLight(BACK_LED_PIN);break;
			case 'n': turnOffLight(BACK_LED_PIN); break;
			case 'J':
				if (value != "") {
					moveServo(value.toInt());
				}
				break;
			case 'K':
				if (value != "") {
					moveServo(value.toInt());
				}
				break;
				*/
		}
	}
}
ControllerClass Controller;