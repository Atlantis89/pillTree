void signalToTakePillState() 
{
	Serial.println("Debug: signalToTakePillState");
	//treeState = pillOutput;

	//shaking tree until someone goes near to the pillbox
	while (treeState == States::signalToTakePill)
	{
		aktuelleZeit = millis();
		if (entfernung() >= min_entfernung)
		{
			baumWackeln(baumwackler, aktuelleZeit);
			//LED strip zum leuchten bringen
			ledPulse();
			//TODO: code is blocking here... try to unblock the code
			Serial.println("Debug: Baum wackelt, Dose leuchtet");
		}
		else 
		{
			treeState = States::pillOutput;
			Serial.println("Debug: wechselt State zu pillOutput");
		}

	}
}

