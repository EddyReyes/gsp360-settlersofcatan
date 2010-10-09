#include "map.h"



//returns true if the player wins
bool map::calculateVictoryPoints(Game* g)
{
	int tempVP = 0;

	tempVP += 5 - g->p[g->activePlayer].getNumUnusedSettlements();//settlements

	tempVP += ((4 - g->p[g->activePlayer].getNumUnusedCities()) * 2);//cities

	tempVP += g->p[g->activePlayer].getNumUsedVictoryPoints();//played victory points

	if(g->p[g->activePlayer].getHasLargestArmy())
		tempVP += 2;//largest army

	if(g->p[g->activePlayer].getHasLongestRoad())
		tempVP += 2;//longest road

	g->p[g->activePlayer].setVictoryPoints(tempVP);//sets the player's victory points

	if(tempVP >= 10)
		return true;
	return false;
}

//function to calculate the largest army
void map::calcLargestArmy(Game* g)
{
	if(g->p[g->activePlayer].getNumUsedSoldiers() >= 3)
	{
		if(g->ownerLargestArmy == NULL)
		{
			g->p[g->activePlayer].awardLargestArmy();//the player is the first to get to 3
			g->ownerLargestArmy = &g->p[g->activePlayer];
		}
		else if(g->p[g->activePlayer].getNumUsedSoldiers() > g->ownerLargestArmy->getNumUsedSoldiers())
		{
			g->p[g->activePlayer].awardLargestArmy();
			g->ownerLargestArmy->retractLargestArmy();
		}
	}
}

void map::steal(Game* g, int victim)
{
	if(g->activePlayer != victim)//cant steal from self
	{
		int totalCards = 0;
		totalCards += g->p[victim].getResource(WHEAT);
		totalCards += g->p[victim].getResource(WOOD);
		totalCards += g->p[victim].getResource(BRICK);
		totalCards += g->p[victim].getResource(STONE);
		totalCards += g->p[victim].getResource(SHEEP);

		int stolenCard = rand() % totalCards + 1;
		char stolenType = ' ';

		if(stolenCard < g->p[victim].getResource(WHEAT) && g->p[victim].getResource(WHEAT) > 0)
			stolenType = WHEAT;
		else if(stolenCard < g->p[victim].getResource(WHEAT) + g->p[victim].getResource(WOOD)  && g->p[victim].getResource(WOOD) > 0)
			stolenType = WOOD;
		else if(stolenCard < g->p[victim].getResource(WHEAT) + g->p[victim].getResource(WOOD) + g->p[victim].getResource(BRICK) && g->p[victim].getResource(BRICK) > 0)
			stolenType = BRICK;
		else if(stolenCard < g->p[victim].getResource(WHEAT) + g->p[victim].getResource(WOOD) + g->p[victim].getResource(BRICK) + g->p[victim].getResource(STONE) && g->p[victim].getResource(STONE) > 0)
			stolenType = STONE;
		else if(g->p[victim].getResource(SHEEP) > 0)
			stolenType = SHEEP;

		g->p[g->activePlayer].changeResource(stolenType, 1);
		g->p[victim].changeResource(stolenType, -1);
	}
}

void map::thiefIsRolled(Game* g)//, int numPlayers)//since this is in the game class, it shouldnt need to be passed
{
	int* numCardsToRemove;
	numCardsToRemove = new int[g->numPlayers];
	int totalCards = 0;

	for(int i = 0; i < g->numPlayers; i++)
	{
		totalCards = 0;
		totalCards += g->p[i].getResource(WHEAT);
		totalCards += g->p[i].getResource(WOOD);
		totalCards += g->p[i].getResource(BRICK);
		totalCards += g->p[i].getResource(STONE);
		totalCards += g->p[i].getResource(SHEEP);

		if(totalCards > 7)
		{
			if(totalCards % 2 == 1)
			{
				totalCards--;
				numCardsToRemove[i] = totalCards / 2;
				totalCards++;
			}
			else
				numCardsToRemove[i] = totalCards / 2;

			while(numCardsToRemove[i] != 0)
			{
				char stolenType = ' ';
				int randCard = (rand() % totalCards) + 1;

				if(randCard < g->p[i].getResource(WHEAT))
					stolenType = WHEAT;
				else if(randCard < g->p[i].getResource(WHEAT) + g->p[i].getResource(WOOD))
					stolenType = WOOD;
				else if(randCard < g->p[i].getResource(WHEAT) + g->p[i].getResource(WOOD) + g->p[i].getResource(BRICK))
					stolenType = BRICK;
				else if(randCard < g->p[i].getResource(WHEAT) + g->p[i].getResource(WOOD) + g->p[i].getResource(BRICK) + g->p[i].getResource(STONE))
					stolenType = STONE;
				else
					stolenType = SHEEP;

				g->underlyingBoard->rsc.returnToResourcePool(stolenType, 1);
				g->p[i].changeResource(stolenType, -1);
				numCardsToRemove[i]--;
				totalCards--;
			}//end of while(numCardsToRemove[i] != 0)
		}//end of if(totalCards > 7)
	}//end of for(int i = 0; i < numPlayers; i++)

	delete [] numCardsToRemove;
}

void map::playMonopolyCard(char type, Game * g)
{
	int amount = 0;
	for (int i = 0; i < g->numPlayers; ++i)
	{
		amount += g->p[i].getResource(type);
		g->p[i].changeResource(type, - (g->p[i].getResource(type)));
	}
	g->p[g->activePlayer].changeResource(type, amount);
}