void pillOutputState() 
{
	Serial.println("Debug: pillOutPutState");
	//�berpr�fen ob immer noch jemand vor der dose steht. wenn nicht wieder in vorherige state zur�ckkehren
	while (treeState == States::pillOutput)
	{
		if (entfernung() <= min_entfernung)
		{
			if(pillsDay > 0 && pillsDay <= 8)
			{
				moveToPosition(pillsDay);
				delay(150);
				treeState = States::takePill;
			}
		}
		else 
		{
			treeState = States::signalToTakePill;
		}
	}


	treeState = takePill;
}