#include <Arduino.h>
#include <AccelStepper.h>

// Define pin connections & motor's steps per revolution
const int dirPin_x = 16;
const int stepPin_x = 17;
const int stepsPerRevolution = 3200;
const int enablePin_x = 18;
const int enablePin_y = 21;
const int dirPin_y = 19;
const int stepPin_y = 20;

AccelStepper stepper_x = AccelStepper(1, stepPin_x, dirPin_x);
AccelStepper stepper_y = AccelStepper(1, stepPin_y, dirPin_y);

//const int limit_power_x = 10;
//const int limit_x = 11;
const int limit_power_y = 14;
const int limit_y = 15;
int initial_homeing_x = -1;
int initial_homeing_y = -1;

void setup()
{
	// Declare pins as Outputs
 	pinMode(stepPin_x, OUTPUT);
	pinMode(dirPin_x, OUTPUT);
 	pinMode(stepPin_y, OUTPUT);
	pinMode(dirPin_y, OUTPUT);

  	//digitalWrite(enablePin_x,HIGH);
  	//digitalWrite(enablePin_y,HIGH);

	stepper_x.setMaxSpeed(5000);
	stepper_y.setMaxSpeed(5000);
	stepper_x.setAcceleration(200);
	stepper_y.setAcceleration(200);

	pinMode(limit_y, INPUT);            // homing switch pin
	gpio_pull_down(limit_y);

	//set limit pin power
	digitalWrite(limit_power_y,HIGH);
	//digitalWrite(limit_power_x,HIGH);
	//calibrating to y origin

	Serial.println("\t[go to origin]");

	stepper_x.setMaxSpeed(5000);
	stepper_y.setMaxSpeed(5000);
	stepper_x.setAcceleration(200);
	stepper_y.setAcceleration(200);

	while(!digitalRead(limit_y))  //pull-up resistor keeps it high, press makes it low
		{         
		stepper_y.moveTo(initial_homeing_y);
		stepper_y.run();
		initial_homeing_y--;
		delay(3);
		}
	stepper_y.setCurrentPosition(0);
	initial_homeing_y=1;

	while(digitalRead(limit_y))  //pull-up resistor keeps it high, press makes it low
		{     
		stepper_y.moveTo(initial_homeing_y);
		stepper_y.run();
		initial_homeing_y++;
		delay(3);
		}

	stepper_y.setCurrentPosition(0);
	Serial.println("y origin");
}
void loop()
{
	// put your main code here, to run repeatedly:
	digitalWrite(LED_BUILTIN, HIGH);
	delay(1);
	digitalWrite(LED_BUILTIN, LOW);
	delay(24);
}