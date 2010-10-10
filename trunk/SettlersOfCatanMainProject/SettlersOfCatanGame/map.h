#pragma once

// yo dawg, I heard you will need a Game class. so I'm putting a Game class before the Game class so you can declare before you declare.
class Game;
class TradeBank;

#include "sdl/sdl.h"
#include "sdl/sdl_ttf.h"
#include <iostream>
#include <ctime>
#include <windows.h>
#include <string> 
#include "dice.h"
#include "edge.h"
#include "node.h"
#include "center.h"
#include "stndrd.h"
#include "player.h"
#include "game.h"
#include "tradebank.h"

using namespace std;

class map
{
private:
	//===surfaces used for images===============
	SDL_Surface *playerTag;
	SDL_Surface *resourceListMsg[5];
	SDL_Surface *tradeCard;
	SDL_Surface *buildCard;
	SDL_Surface *resourceCard;
	SDL_Surface *background1;
	SDL_Surface *roadTile[4];
	SDL_Surface *settlementTile[4];
	SDL_Surface *cityTile[4];
	SDL_Surface *testSelect;
	SDL_Surface *hexTile;
	SDL_Surface *DevHand;
	SDL_Surface *woodTile;
	SDL_Surface *sheepTile;
	SDL_Surface *brickTile;
	SDL_Surface *stoneTile;
	SDL_Surface *wheatTile;
	SDL_Surface *chitTile[10];
	SDL_Surface *thief;
	SDL_Surface *pickToTrade;
	SDL_Surface *standardLegend;
	SDL_Surface *cancelLegend;
	SDL_Surface *extraTradeRules;


	//=== map-only load_image and apply_surface
	SDL_Surface *load_image( std::string filename );
	void apply_surface(int x, int y,SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip);


public:
	//============Trade stuff=====================
	TradeBank* tradebank;

	//============PLACEHOLDER NUM FOR FREE TWO ROADS AND FREE TWO RESOURCES
	int placeholderFREE;
	int soundQueue;

	// ============== DICE STUFF =========================
	Dice dice;
	int dice1;
	int dice2;
	bool rolledDice;

	//=== the map is initialized with an internal resourceDeck and developmentDeck
	rsc rsc;
	dvc dvc;


	// =============== MAPSTATES (THEY ARE PUBLIC BECAUSE GAME.CPP NEEDS THEM SOMETIMES ====================
	int mapState;
	static const int BEGINTURN = 0; // start state to trigger dice roll and such;
	static const int MAP = 1; // play state
	static const int BUILDCARD = 2; // play state
	static const int RESOURCELIST = 3; // play state
	static const int DEVHAND = 4; // play state
	static const int TRADE = 5; // play state
	static const int BUILDROAD = 6; // play state
	static const int BUILDSETTLEMENT = 7; // play state
	static const int BUILDCITY = 8; // play state
	static const int TURNONESETTLEMENT = 9;
	static const int TURNONEROAD = 10;
	static const int TURNTWOSETTLEMENT = 11;
	static const int TURNTWOROAD = 12;
	static const int FREETWOROADS = 13;
	static const int FREETWORESOURCES = 14;
	static const int PICKMONOPOLY = 15;
	static const int SETTHETHIEF = 16;
	static const int TRADETARGET = 17;
	static const int TRADEPLAYERSCREEN = 18;
	static const int TRADEBANKHARBORSCREEN = 19;
	static const int SOMEONEWON = 20;
	static const int ENDTURN = 99; // play state (mainly to trigger the changing of players in game.cpp)
	static const int NOT_A_PLAYER = 4; // play state (mainly to trigger the changing of players in game.cpp)


	//==============MAP INITIALIZERS SETUP IN THE map.cpp FILE===========
	int overallTurn;
	Edge myEdges[144];
	Node myNodes[54];
	Center myCenters[19];
	int myChits[18];
	map::map();
	Node * getNode(Node * population, int popCount, int ID);
	int getEdge(Edge * population, int popCount, int start, Node * from);
	int getEdgeFromCount(Edge * population, int popCount, Node * from);
	char randomHarbor(int resource[]);
	void setHarbor(Node* harbor);
	void initializeCenters(void);

	map::~map();


	//====CONSTRUCTION DEVICS HANDLED IN THE mapConstruct.cpp FILE=============
	int nodeSelectron;
	int roadSelectron;
	int centerSelectron;
	void map::whichNodeIsWithin(int const & x, int const & y, int radius);
	void map::whichRoadIsWithin(int const & x, int const & y, int radius);
	void map::whichCenterIsWithin(int const & x, int const & y, int radius);
	bool map::constructRoadOnMap(Game * g);
	bool map::constructSettlementOnMap(Game * g);
	bool map::constructSettlementOnMapAnywhere(Game * g);
	bool map::constructCityOnMap(Game * g);
	bool map::constructThiefOnMap(Game * g);



	//=======DRAW FUNCTIONS HANDLED IN THE mapImage.cpp FILE===============
	void map::draw(SDL_Surface * screen, Game * g);
	void map::loadImages(void);
	void map::initializeImages(void);
	void map::drawDiceRoll(SDL_Surface * screen, Game * g);
	void map::drawtradeCard(SDL_Surface * screen, Game* g);
	void map::drawDevHand(SDL_Surface * screen, Game * g);
	void map::drawResourceList(SDL_Surface * screen, Game * g);
	void map::drawBuildCard(SDL_Surface * screen);
	void map::drawNodeSelectron(SDL_Surface * screen);
	void map::drawRoadSelectron(SDL_Surface * screen);
	void map::drawBoard(SDL_Surface * screen);
	void map::drawPlayerTag(SDL_Surface * screen, Game * g);
	void map::drawWinScreen(SDL_Surface * screen);
	void map::drawResourceGrab(SDL_Surface * screen);
	void map::drawCenterSelectron(SDL_Surface * screen);
	void map::drawPickTradeTarget(SDL_Surface * screen, Game * g);
	void map::drawThiefExplanation(SDL_Surface * screen, Game * g);
	void map::drawCancelInstructions(SDL_Surface * screen, Game * g);
	void map::drawStandardInstructions(SDL_Surface * screen, Game * g);
	void map::drawInstructions(SDL_Surface * screen, Game * g);
	void map::drawFreeSettlementInstructions(SDL_Surface * screen, Game * g);
	void map::drawFreeRoadInstructions(SDL_Surface * screen, Game * g);
	void map::drawExtraTradeRules(SDL_Surface * screen, Game * g);
	void map::drawVictoryPoints(SDL_Surface * screen, Game * g);
	void map::shutdownImages(void);




	
	//========HANDLE INPUTS, ALL IN THE mapInput.cpp FILE================
	void map::handleInput(SDL_Event e, Game * g);
	void map::handleInput_BEGINTURN(SDL_Event e, Game * g);
	void map::handleInput_MAP(SDL_Event e, Game * g);
	void map::handleInput_BUILDCARD(SDL_Event e, Game * g);
	void map::handleInput_RESOURCELIST(SDL_Event e, Game * g);
	void map::handleInput_DEVHAND(SDL_Event e, Game * g);
	void map::handleInput_BUILDROAD(SDL_Event e, Game * g);
	void map::handleInput_BUILDSETTLEMENT(SDL_Event e, Game * g);
	void map::handleInput_BUILDCITY(SDL_Event e, Game * g);
	void map::handleInput_TURNONESETTLEMENT(SDL_Event e, Game * g);
	void map::handleInput_TURNONEROAD(SDL_Event e, Game * g);
	void map::handleInput_TURNTWOSETTLEMENT(SDL_Event e, Game * g);
	void map::handleInput_TURNTWOROAD(SDL_Event e, Game * g);
	void map::handleInput_FREETWOROADS(SDL_Event e, Game * g);
	void map::handleInput_FREETWORESOURCES(SDL_Event e, Game * g);
	void map::handleInput_PICKMONOPOLY(SDL_Event e, Game * g);
	void map::handleInput_SETTHETHIEF(SDL_Event e, Game * g);
	void map::handleInput_TRADETARGET(SDL_Event e, Game * g);
	void map::handleInput_TRADEPLAYERSCREEN(SDL_Event e, Game * g);
	void map::handleInput_TRADEBANKHARBORSCREEN(SDL_Event e, Game * g);

	//=======MAP TTFs====================
	TTF_Font *font;
	SDL_Color textColor;


	//mapGameplay.cpp
	bool map::calculateVictoryPoints(Game* g);
	bool map::calculateLongestRoad(Game* g);
	void map::thiefIsRolled(Game* g);
	void map::steal(Game* g, int victim);
	void map::calcLargestArmy(Game* g);
	void map::playMonopolyCard(char type, Game * g);

};