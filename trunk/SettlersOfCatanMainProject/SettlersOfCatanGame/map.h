#pragma once

#include "sdl/sdl.h"
#include <iostream>
#include <ctime>
#include <windows.h>
#include "edge.h"
#include "node.h"
#include "center.h"
#include "stndrd.h"
#include "player.h"

using namespace std;

class map
{
private:
	//===surfaces used for images===============
	SDL_Surface *tradeCard;
	SDL_Surface *buildCard;
	SDL_Surface *resourceCard;
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

	//=== the map is initialized with an internal resourceDeck and developmentDeck
	rsc rsc;
	dvc dvc;

	//=== map-only load_image and apply_surface
	SDL_Surface *load_image( std::string filename );
	void apply_surface(int x, int y,SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip);


public:
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
	static const int ENDTURN = 99; // play state (mainly to trigger the changing of players in game.cpp)


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
	int randomHarbor(int resource[]);
	void setHarbor(Node* harbor);
	void initializeCenters(void);


	//====CONSTRUCTION DEVICS HANDLED IN THE mapConstruct.cpp FILE=============
	int nodeSelectron;
	int roadSelectron;
	void map::whichNodeIsWithin(int const & x, int const & y, int radius);
	void map::whichRoadIsWithin(int const & x, int const & y, int radius);
	bool map::constructRoadOnMap(player * p);
	bool map::constructSettlementOnMap(player * p);
	bool map::constructSettlementOnMapAnywhere(player * p);



	//=======DRAW FUNCTIONS HANDLED IN THE mapImage.cpp FILE===============
	void map::draw(SDL_Surface * screen, player * p);
	void map::loadImages(void);
	void map::initializeImages(void);
	void map::drawtradeCard(SDL_Surface * screen);
	void map::drawDevHand(SDL_Surface * screen);
	void map::drawResourceList(SDL_Surface * screen, player * p);
	void map::drawBuildCard(SDL_Surface * screen);
	void map::drawNodeSelectron(SDL_Surface * screen);
	void map::drawRoadSelectron(SDL_Surface * screen);
	void map::drawBoard(SDL_Surface * screen);
	void map::shutdownImages(void);




	
	//========HANDLE INPUTS, ALL IN THE mapInput.cpp FILE================
	void map::handleInput(SDL_Event e, player * p);
	void map::handleInput_BEGINTURN(SDL_Event e, player *p);
	void map::handleInput_MAP(SDL_Event e, player * p);
	void map::handleInput_BUILDCARD(SDL_Event e, player * p);
	void map::handleInput_RESOURCELIST(SDL_Event e, player * p);
	void map::handleInput_DEVHAND(SDL_Event e, player * p);
	void map::handleInput_TRADE(SDL_Event e, player * p);
	void map::handleInput_BUILDROAD(SDL_Event e, player * p);
	void map::handleInput_BUILDSETTLEMENT(SDL_Event e, player * p);
	void map::handleInput_BUILDCITY(SDL_Event e, player * p);
	void map::handleInput_TURNONESETTLEMENT(SDL_Event e, player * p);
	void map::handleInput_TURNONEROAD(SDL_Event e, player * p);
	void map::handleInput_TURNTWOSETTLEMENT(SDL_Event e, player * p);
	void map::handleInput_TURNTWOROAD(SDL_Event e, player * p);

};