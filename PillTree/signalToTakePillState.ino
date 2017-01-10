void signalToTakePillState() 
{
	Serial.println("Debug: signalToTakePillState");

	//shaking tree until someone goes near to the pillbox
	while (treeState == States::signalToTakePill)
	{

		if (entfernung() > min_entfernung)
		{
			time = millis() - previousMillis;
			baumWackeln2(baumwackler, time);
			Serial.println("Debug: Baum wackelt");
		}
		else 
		{
			baumwackler.write(90);
			treeState = States::pillOutput;
			Serial.println("Debug: wechselt State zu pillOutput");
		}

	}
}

