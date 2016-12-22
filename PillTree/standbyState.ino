void standbyState() 
{
	//nothing else to do here
	Serial.println("Debug: standbyState");
	//reset zur vorführung
	if (nextLeafToPull == 2) //sprich, drittes blatt war oben
	{
		Serial.println("Debug: refill");
		nextLeafToPull = 0;
		blattRunter(blatt1, 1, 200);
		blattRunter(blatt2, 1, 200);
		blattRunter(blatt3, 1, 200);
		//zum nachfüllen der pillen
		moveToPosition(1);
		delay(REFILL_DELAY);
		moveToPosition(2);
		delay(REFILL_DELAY);
		moveToPosition(3);
		delay(REFILL_DELAY);
		moveToPosition(0);
	}
	delay(STANDBY_DELAY);
	Serial.println("Debug: wechsel in signalToTakePill");
	treeState = States::signalToTakePill;
	/*while (treeState == States::standby) 
	{
	}*/
}
