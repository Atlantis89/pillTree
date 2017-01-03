//Steppermotor to rotate the motor in one of the 8 possible positions. range from 0 - 8
void moveToPosition(int position)
{
	pillStepper.runToNewPosition(512 * position);
}

//Berechnung der Entfernung mit Hilfe des Abstandssensors
long entfernung() {
	long dauer, entfernung;
	digitalWrite(pin_annaehrung_trigger, LOW);
	delayMicroseconds(2);
	digitalWrite(pin_annaehrung_trigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(pin_annaehrung_trigger, LOW);
	dauer = pulseIn(pin_annaehrung_echo, HIGH);

	return entfernung = (dauer / 2) / 29.1; // Entfernung in cm
}

//Blatt am Baum runterlassen mit Hilfe eines Servos
void blattRunter(Servo servo, int schrittweite, int wartezeit) {
	int winkel = schrittweite;
	while (winkel <= 178) {
		servo.write(winkel);
		delay(wartezeit);
		winkel = winkel + schrittweite;
	}
}
//Blatt hochziehen mit Hilfe eines Servos
void blattHoch(Servo servo, int schrittweite, int wartezeit) {
	int winkel = 180 - schrittweite;
	while (winkel > 0) {
		servo.write(winkel);
		delay(wartezeit);
		winkel = winkel - schrittweite;
	}
}
//Hilfsfunktion um den Baum mit Hilfe von Servos zum wackeln zu bringen
void wackeln(Servo servo, int wartezeit) {
	servo.write(80);
	delay(wartezeit);
	servo.write(100);
	delay(wartezeit);
}
//Baum mit Hilfe von Servos zum wackeln bringen.
void baumWackeln(Servo servo, long aktuelleZeit) 
{

	if (aktuelleZeit <= pille1_zeit + max_wackel_zeit / 3) 
	{
		Serial.print("Debug: shake speed 1.");
		Serial.println(aktuelleZeit);
		wackeln(servo, 500);
	}
	else 
	{
		if (aktuelleZeit >= pille1_zeit + max_wackel_zeit / 3 && aktuelleZeit <= pille1_zeit + max_wackel_zeit / 3 * 2) 
		{
			Serial.print("Debug: shake speed 2.");
			Serial.println(aktuelleZeit);
			wackeln(servo, 300);
		}
		else 
		{
			Serial.print("Debug: shake speed 3.");
			Serial.println(aktuelleZeit);
			wackeln(servo, 200);
		}
	}
}
void baumWackeln2(Servo servo, unsigned long time) {
	
	previousMillis = millis();
	if (time <= max_wackel_zeit / 3)
	{
		wackeln(servo, 500);
	}
	else if (time >= (max_wackel_zeit / 3) * 2)
	{
		wackeln(servo, 300);
	}
	else
	{
		wackeln(servo, 200);
	}
}
//LED Leiste pulsieren (bis jetzt ein blockierender durchlauf)
/*
void ledPulse() 
{
	for (int f = 0; f <= 150; f++) {
		for (int i = 0; i <= strip.numPixels(); i++) {
			strip.setPixelColor(i, strip.Color(f, 0, 0));
		}
		strip.show();
		delay(20);
	}

	for (int f = 150; f >= 0; f--) {
		for (int i = 0; i <= strip.numPixels(); i++) {
			strip.setPixelColor(i, strip.Color(f, 0, 0));
		}
		strip.show();
		delay(20);
	}
	//delay(150);
}*/
