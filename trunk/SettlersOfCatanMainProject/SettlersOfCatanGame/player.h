#pragma once

#include "resourceCards.h"
#include "developmentCards.h"

class player
{
private:
	char color;
	int currentVictoryPoints;
	int usedSoldiers;
	int usedVictoryPoints;
	int inHandVictoryPoints;
	int inHandSoldiers;
	int inHandMonopolies;
	int inHandTwoRoads;
	int inHandYearOfPlenty; // TWO OF ANY RESOURCE
	bool hasLongestRoad;
	bool hasLargestArmy;

public: 
	int wood;
	int wheat;
	int stone;
	int sheep;
	int brick;
	int numUnusedRoads;
	int numUnusedSettlements;
	int numUnusedCities;
	int ID;
	player::player(void);
	//void player::setPlayer(char a_color);
	void player::drawResource(rsc* resDeck, char type, int num);
	void player::addVictoryPoint(void)			{ currentVictoryPoints++; }
	void player::addUsedSoldier(void)			{ usedSoldiers++; }
	void player::addUsedVictoryPoint(void)		{ usedVictoryPoints++; }
	void player::drawDevCard(dvc* devDeck);
	bool player::checkBuildSomething(char type, dvc* dvc);
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
	//bool player::CheckWin();

	//added these for the calcVictoryPoints function
	void setVictoryPoints(int vp) { currentVictoryPoints = vp; }
	int getNumUnusedSettlements() { return numUnusedSettlements; }
	int getNumUnusedCities() { return numUnusedSettlements; }
	bool getHasLargestArmy() { return hasLargestArmy; }
	bool getHasLongestRoad() { return hasLongestRoad; }
	int getNumUsedSoldiers() { return usedSoldiers; }
	int getNumUnusedRoads() { return numUnusedRoads; }
	int getNumUsedVictoryPoints() { return usedVictoryPoints; }
};



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