#include "resourceCards.h"
#include "developmentCards.h"

class player
{
private:
	bool active;
	char color;
	int wood;
	int wheat;
	int stone;
	int sheep;
	int brick;
	int currentVictoryPoints;
	int usedSoldiers;
	int usedVictoryPoints;
	int inHandVictoryPoints;
	int inHandSoldiers;
	int inHandMonopolies;
	int inHandTwoRoads;
	int inHandYearOfPlenty; // TWO OF ANY RESOURCE
	int numUnusedRoads;
	int numUnusedSettlements;
	int numUnusedCities;
	bool hasLongestRoad;
	bool hasLargestArmy;

public: 
	player::player(void){active = false;}
	void player::setPlayer(char a_color);
	void player::drawResource(rsc* resDeck, char type, int num);
	void player::addVictoryPoint(void)			{ currentVictoryPoints++; }
	void player::addUsedSoldier(void)			{ usedSoldiers++; }
	void player::addUsedVictoryPoint(void)		{ usedVictoryPoints++; }
	void player::drawDevCard(dvc* devDeck);
	bool player::checkBuildSomething(char type);
	void player::actuallyBuildSomething(char type, rsc* rsc, dvc* dvc);
	void player::awardLongestRoad(void);
	void player::retractLongestRoad(void);
	void player::awardLargestArmy(void);
	void player::retractLargestArmy(void);
	void player::playDevCard(char type);
	int player::getResource(char type);
	void player::changeResource(char type, int num);
	//void player::addResource(char type, int num);
	//void player::removeResource(char type, int num);
	bool player::CheckWin();
};

void player::setPlayer(char a_color)
{
	active = true;
	color = a_color;
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

bool player::checkBuildSomething(char type)
{
	switch(type)
	{
		case 'R': if(numUnusedRoads > 0) {return true;}; break;
		case 'S': if(numUnusedSettlements > 0) {return true;}; break;
		case 'C': if(numUnusedCities > 0) {return true;}; break;
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
	currentVictoyPoints += cityPoints;

	currentVictoryPoints += numUsedVictoryPoints;

	if(hasLargestArmy)
		currentVictoryPoints += 2;
	
	if(hasLongestRoad)
		currentVictoryPoints += 2;

	if(currentVictoryPoints >= 10)
		return true;

	return false;//player hasnt won yet
}

/*

Settlement // and NULL
	x,y
	what resources next to it // ONLY BE USED ONCE! (SECOND SETTLEMENT)
	owner
	harborType
	type(settlement//city)

Roads (as the edges)
	x,y
	owner

harborTypeEnum
	None
	3:1
	sheep
	brick
	wheat
	ore
	wood

Tile
	resource type
	6 adjacent settlement
	6 road positions
	resource chit value
	isRobberHere

//////resourceBank

//////developmentBank

start menu screen
	pick 3 or 4 players?

board setup process (automated)
	randomize tiles and harbors
	build the graph

player setup process
	establish order of turns
	place settlements
	recieve resources for second settlement
	player

while running
{

change show player turn
chance to play dev card
check()
dice roll
	chance to play dev card
	check()
	trade
	spend resources on
		settlements
		check()
		roads
		check()
		cities
		check()
		dev cards
	end turn
}

check
{
who has
	longest road
		who currently has it
			if they still have it
		who has a greater amount than that player (or 4)
	largest army

victory points from
	settlements
	cities
	longest road
	largest army
	show victory point cards
}
*/