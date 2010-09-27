//add these functions to the playerClass
//------------------------------int getVictoryPoints() { return currentVictoryPoints; }
//void setVictoryPoints(int vp) { currentVictoryPoints = vp; }
//int getNumUnusedSettlements() { return numUnusedSettlements; }
//int getNumUnusedCities() { return numUnusedSettlements; }
//bool getHasLargestArmy() { return hasLargestArmy; }
//bool getHasLongestRoad() { return hasLongestRoad; }
//int getNumUsedSoldiers() { return numUsedSoldiers; }
//int getNumUnusedRoads() { return numUnusedRoads; }
//int getUsedVictoryPoints() { return numUsedVictoryPoints; }

//need these 2 in the game class
//player* ownerLargestArmy;
//player* ownerLongestRoad;

//in a function that calls this, have it set the win thing if the number returned >= 10
//the player class really doesnt need variable for victory points\
 if its removed, set and get victory points can be removed
int calculateVictoryPoints(player* p)
{
	int tempVP = 0;

	tempVP += 5 - p->getNumUnusedSettlements();
	tempVP += (4 - p->getNumUnusedCities()) * 2;

	tempVP += p->getNumUsedVictoryPoints();

	if(p->getHasLargestArmy())
		tempVP += 2;

	if(p->getHasLongestRoad())
		tempVP += 2;

	p->setVictoryPoints(tempVP);

	return tempVP;
}

//function to calculate the largest army
void calcLargestArmy(player* p)
{
	if(p->getNumUsedSoliders() >= 3)
	{
		if(ownerLargestArmy == NULL)
		{
			p->awardLargestArmy();//the player is the first to get to 3
			ownerLargestArmy = p;
		}
		else if(p->getNumUsedSoliders() > ownerLargestArmy->getNumUsedSoldiers())
		{
			p->awardLargestArmy();
			currentLargestArmy = p->NumUsedSoldiers();
			ownerLargestArmy->retractLargestArmy();
		}
	}
}

//function to calculate the longest road
void calcLongestRoad(player* p)
{
	if(15 - p->getNumUnusedRoads() >= 5)
	{
		if(ownerLongestRoad == NULL)
		{
			//calc here
		}
		else if((15 - p->getNumUnusedRoads()) > (15 - ownerLongestRoad->getNumUnusedRoads()))
		{
			//calc here too
		}
		
	}
}