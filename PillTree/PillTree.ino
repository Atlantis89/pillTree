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
//end stepper motor
//blätter
Servo blatt1;
const int blatt1_pin = 13; // Pin Blatt 1
Servo blatt2;
const int blatt2_pin = 12; // Pin Blatt 2
Servo blatt3;
const int blatt3_pin = 11; // Pin Blatt 3
//end blätter
//wackeln
Servo baumwackler;
const int baumwackler_pin = 10; // Pin Baumwackler
const long max_wackel_zeit = 60000; // Maximale Wackelzeit des Baumes 1 Minuten
//end wackeln
//pillen (ehmaliger reed)
//const int pille1_pin = A4; // Pin Pille 1 reed
const long pille1_zeit = 60000; // Zeit in Millisekunden nach Start um Pille 1 zu nehmen;
//TODO: maybe not needed. if we only use one reed switch
//const int pille2_pin = 8; // Pin Pille 2
//const long pille2_zeit = 60000; // Zeit in Millisekunden nach Start um Pille 2 zu nehmen;
//const int pille3_pin = 7; // Pin Pille 3
//const long pille3_zeit = 120000; // Zeit in Millisekunden nach Start um Pille 3 zu nehmen;
//end pillen
//anneaherung
const int pin_annaehrung_echo = 6; // Pin Annaehrung Echo
const int pin_annaehrung_trigger = 5; // Pin Annaehrung Trigger
const int min_entfernung = 10; //Mindestentfernung 50 cm zu Dose
//end anneaherung
//led Strip
//const int LED_STRIP_PIN = 8;
//end led Strip
//delays
//const int DELAY = 3000;
const int REFILL_DELAY = 5000;
const int STANDBY_DELAY = 1000 * 20;

//long aktuelleZeit;
//long startTime;
unsigned long time;
unsigned long previousMillis = 0;
unsigned long interval = 10000;
//end delays

enum States :int
{
	standby,
	signalToTakePill,
	pillOutput,
	takePill
};

int nextLeafToPull = 0;
//should never be out of range of 1 - 8
int pillsDay = 1;
bool pillTaken = false;

States treeState;
AccelStepper pillStepper = AccelStepper(HALFSTEP, STEPPER_PIN1, STEPPER_PIN3, STEPPER_PIN2, STEPPER_PIN4);
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);
//== end initialisierung ================================

void setup()
{
	Serial.begin(9600);
	treeState = States::standby;
	//stepper motor
	pillStepper.setMaxSpeed(STEPPER_SPEED);
	pillStepper.setAcceleration(STEPPER_SPEED * 2);
	//end stepper motor
	// Blätterservos initialisieren
	blatt1.attach(blatt1_pin);
	blatt2.attach(blatt2_pin);
	blatt3.attach(blatt3_pin);
	//end blätterservos
	//baumwackler
	baumwackler.attach(baumwackler_pin);
	//end baumwackler
	//Taster zum Anzeigen ob Pille genommen. 
	pinMode(8, INPUT_PULLUP);
	//end pillen
	//annaeherung
	pinMode(pin_annaehrung_trigger, OUTPUT);
	pinMode(pin_annaehrung_echo, INPUT);
	//end annaeherung
	//led leiste
	//strip.begin();
	//strip.show(); // Initialize all pixels to 'off'
	//end led leiste
	//Servos resetten
	Serial.println("Servo reset");
	baumwackler.write(90);
	blattRunter(blatt1, 2, 100);
	blattRunter(blatt2, 2, 100);
	blattRunter(blatt3, 2, 100);

}

void loop() 
{
	delay(1000);
	switch (treeState)
	{
	case standby:standbyState();
		break;
	case signalToTakePill: signalToTakePillState();
		break;
	case pillOutput: pillOutputState();
		break;
	case takePill: takePillState();
		break;
	default: Serial.println("Something strange happend!");
		break;
	}
	
	//delay(DELAY);
}