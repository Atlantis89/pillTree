/*
this script resets the project prototype
*/
#include <AccelStepper.h>
//#include <Adafruit_NeoPixel.h>
#include <Servo.h>

//== initialisierung ====================================
//stepper motor
#define HALFSTEP 8
#define STEPPER_SPEED 800
#define STEPPER_PIN1 A0
#define STEPPER_PIN2 A1
#define STEPPER_PIN3 A2
#define STEPPER_PIN4 A3
AccelStepper pillStepper = AccelStepper(HALFSTEP, STEPPER_PIN1, STEPPER_PIN3, STEPPER_PIN2, STEPPER_PIN4);


Servo blatt1;
const int blatt1_pin = 13; // Pin Blatt 1
Servo blatt2;
const int blatt2_pin = 12; // Pin Blatt 2
Servo blatt3;
const int blatt3_pin = 11; // Pin Blatt 3

Servo baumwackler;
const int baumwackler_pin = 10;

void setup() {
	Serial.begin(9600);

	pillStepper.setMaxSpeed(STEPPER_SPEED);
	pillStepper.setAcceleration(STEPPER_SPEED * 2);

	blatt1.attach(blatt1_pin);
	blatt2.attach(blatt2_pin);
	blatt3.attach(blatt3_pin);

	baumwackler.attach(baumwackler_pin);

}

String readCommand;
String readAbort = "";
int position = 0;

void loop() {
	if (Serial.available() )
	{
		readCommand = Serial.readString();
	}

	if (readCommand.equals("leafsDown"))
	{
		Serial.println("blatt1 wird runtergelassen");
		blattRunter(blatt1, 2);
		Serial.println("blatt2 wird runtergelassen");
		blattRunter(blatt2, 2);
		Serial.println("blatt3 wird runtergelassen");
		blattRunter(blatt3, 2);
	}

	if (readCommand.equals("wackler"))
	{
		baumwackler.write(90);
	}

	if (readCommand.equals("turn"))
	{
		while (!readAbort.equals("abort"))
		{
			int stepSize = 10;
			position += stepSize;
			pillStepper.runToNewPosition(position++);
			if(Serial.available())
				readAbort = Serial.readString();
		}
		readAbort = "";
		Serial.println(position);
		//pillStepper.runToNewPosition(512);
	}
	if(!readCommand.equals(""))
	{
		Serial.println(readCommand);
	}
	readCommand = "";

	delay(2000);
}

void blattRunter(Servo servo, int schrittweite) {
	int winkel = servo.read();
	while (winkel <= 178) {
		servo.write(winkel);
		delay(100);
		winkel = winkel + schrittweite;
	}
}