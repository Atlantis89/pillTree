void takePillState() 
{
	Serial.println("Debug: takePillState");
	//wenn jemand weggeht ohne pille zu nehmen --> pillsyday - 1 und baumwackeln
	//wenn jemand davorsteht und pille rausnimmt --> stepper auf 0 und standby und blatt wird hochgezogen

	while (treeState == States::takePill)
	{
		//TODO: timer einbauen. wenn 

		//wenn jemand davorsteht und pille nimmt
		if (entfernung() <= min_entfernung && digitalRead(pille1_pin) == HIGH && !pillTaken)
		{
			Serial.println("Debug: Pille genommen");
			if (!pillTaken)
			{
				switch (nextLeafToPull)
				{
				case 0: blattHoch(blatt1, 1, 200);
					pillTaken = true;
					nextLeafToPull = 1;
					break;
				case 1: blattHoch(blatt2, 1, 200);
					pillTaken = true;
					nextLeafToPull = 2;
					break;
				case 2: blattHoch(blatt3, 1, 200);
					pillTaken = true;
					break;
				default:
					break;
				}
			}
			if (pillsDay == 8) {
				pillsDay = 0;
			}
			else {
				pillsDay++;
			}

			delay(1000);
			moveToPosition(0);
			treeState = States::standby;
		}
		else {
			//jemand stand davor und ist wieder weggegangen ohne eine pille genommen zu haben
			moveToPosition(0);
			pillsDay--;
			delay(10000);//warte 10 sec bis baum wieder signalisiert
			treeState = States::signalToTakePill;
		}
	}
}
