#include "player.h"

player::player(void)
{
	wood = 0; wheat = 0; stone = 0; sheep = 0; brick = 0;
	currentVictoryPoints = 0; usedSoldiers = 0; usedVictoryPoints = 0;
	inHandSoldiers = 0; inHandMonopolies = 0; inHandYearOfPlenty = 0; inHandTwoRoads = 0; inHandVictoryPoints = 0;
	numUnusedRoads = 15; numUnusedSettlements = 5; numUnusedCities = 4;
	hasLongestRoad = false;
	hasLargestArmy = false;
}

int player::getResource(char type)
{
	switch(type)
	{
		case WOOD:	return wood;
		case WHEAT:	return wheat;
		case STONE:	return stone;
		case SHEEP:	return sheep;
		case BRICK:	return brick;
		default: break;
	}
	return -1;
}

void player::changeResource(char type, int num)
{
	switch(type)
	{
	case WOOD: wood += num; break;
	case WHEAT: wheat += num; break;
	case STONE: stone += num; break;
	case SHEEP: sheep += num; break;
	case BRICK: brick += num; break;
	default: break;
	}
}
void player::awardLongestRoad(void)
{
	hasLongestRoad = true;
}
void player::retractLongestRoad(void)
{
	hasLongestRoad = false;
}
void player::awardLargestArmy(void)
{
	hasLargestArmy = true;
}
void player::retractLargestArmy(void)
{
	hasLargestArmy = false;
}

void player::playDevCard(char type)
{
	switch(type)
	{
		case 'S':	if (inHandSoldiers > 0)
					{
						inHandSoldiers--; 
						usedSoldiers++;
					}
				break;
		case 'M':	if (inHandMonopolies > 0)
					{
						inHandMonopolies--; 
					}
				break;
		case 'Y':	if (inHandYearOfPlenty > 0)
					{
						inHandYearOfPlenty--; 
					}
				break;
		case 'T':	if(inHandTwoRoads > 0)
					{
						inHandTwoRoads--; 
					}
				break;
		case 'V':	if(inHandVictoryPoints > 0)
					{
						inHandVictoryPoints--; 
						usedVictoryPoints++;
					}
				break;
		default: break;
	}
}

bool player::checkBuildSomething(char type, dvc * dvc)
{
	switch(type)
	{
		case 'R': if(numUnusedRoads > 0 && brick >= 1 && wood >= 1) {return true;}; break;
		case 'S': if(numUnusedSettlements > 0 && brick >=1 && wood >= 1 && sheep >= 1 && wheat >= 1) {return true;}; break;
		case 'C': if(numUnusedCities > 0 && stone >= 3 && wheat >= 2) {return true;}; break;
		case 'D': if(dvc->drawAvailable() == true && stone >= 1 && wheat >= 1 && sheep >= 1) {return true;}; break;
		default:break;
	}
	return false;
}

void player::actuallyBuildSomething(char type, rsc* rsc, dvc* dvc) //ADD roads,settlements.h and points.
{
	switch(type)
	{
		case 'R':	numUnusedRoads--; 
					rsc->returnToResourcePool(WOOD, 1); 
					rsc->returnToResourcePool(BRICK, 1);
				break;
		case 'S':	numUnusedSettlements--; 
					rsc->returnToResourcePool(WOOD, 1);
					rsc->returnToResourcePool(SHEEP, 1);
					rsc->returnToResourcePool(BRICK, 1);
					rsc->returnToResourcePool(WHEAT, 1);
				break;
		case 'C':	numUnusedCities--; 
					rsc->returnToResourcePool(WHEAT, 2);
					rsc->returnToResourcePool(STONE, 3);
				break;
		case 'D':	drawDevCard(dvc);
					rsc->returnToResourcePool(WHEAT, 1);
					rsc->returnToResourcePool(STONE, 1);
					rsc->returnToResourcePool(SHEEP, 1);
			break;
		default: break;
	}
}

void player::drawDevCard(dvc* devDeck)
{
	char type = devDeck->pullCard();
	switch(type)
	{
		case 'S': inHandSoldiers++; break;
		case 'M': inHandMonopolies++; break;
		case 'Y': inHandYearOfPlenty++; break;
		case 'T': inHandTwoRoads++; break;
		case 'V': inHandVictoryPoints++; break;
		default: break;
	}
}

void player::drawResource(rsc* resDeck, char type, int num)
{
	int count = resDeck->pullFromResourcePool(type, num);
	switch(type)
	{
		case WOOD:	wood += count;		break;
		case WHEAT:	wheat += count;		break;
		case STONE:	stone += count;		break;
		case SHEEP:	sheep += count;		break;
		case BRICK:	brick += count;		break;
		default: break;
	}
}

bool player::CheckWin()
{
	//can take out currentVictoryPoints from the player and put it here, since its calculated each time
	currentVictoryPoints = 0;

	//ill change this to not add more variables
	int settlementPoints  = 5 - numUnusedSettlements;
	currentVictoryPoints += settlementPoints;
	
	int cityPoints = (4 - numUnusedCities) * 2;
	currentVictoryPoints += cityPoints;

	currentVictoryPoints += usedVictoryPoints;

	if(hasLargestArmy)
		currentVictoryPoints += 2;
	
	if(hasLongestRoad)
		currentVictoryPoints += 2;

	if(currentVictoryPoints >= 10)
		return true;

	return false;//player hasnt won yet
}