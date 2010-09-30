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
	rsc rsc;
	dvc dvc;
	SDL_Surface *buildCard;
	SDL_Surface *resourceCard;
	SDL_Surface *roadTile[4];
	SDL_Surface *settlementTile[4];
	SDL_Surface *cityTile[4];
	SDL_Surface *testSelect;
	SDL_Surface *hexTile;
	SDL_Surface *woodTile;
	SDL_Surface *sheepTile;
	SDL_Surface *brickTile;
	SDL_Surface *stoneTile;
	SDL_Surface *wheatTile;
	SDL_Surface *chitTile[10];
	SDL_Surface *load_image( std::string filename );
	void apply_surface(int x, int y,SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip);
public:
	static const int MAP = 1; // play state
	static const int BUILDCARD = 2; // play state
	static const int RESOURCELIST = 3; // play state
	static const int DEVHAND = 4; // play state
	static const int TRADE = 5; // play state
	static const int BUILDROAD = 6; // play state
	static const int BUILDSETTLEMENT = 7; // play state
	static const int BUILDCITY = 8; // play state
	static const int ENDTURN = 99; // play state (mainly to trigger the changing of players in game.cpp)
	int mapState;
	int overallTurn;
	int nodeSelectron;
	int roadSelectron;
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
	void map::draw(SDL_Surface * screen, player * p);
	void map::loadImages(void);
	void map::shutdownImages(void);
	void map::whichNodeIsWithin(int const & x, int const & y, int radius);
	void map::whichRoadIsWithin(int const & x, int const & y, int radius);
	bool map::mouseOverNode(int const & x, int const & y);
	void map::drawTradeScreen(SDL_Surface * screen);
	void map::drawDevHand(SDL_Surface * screen);
	void map::drawResourceList(SDL_Surface * screen, player * p);
	void map::drawBuildCard(SDL_Surface * screen);
	void map::drawNodeSelectron(SDL_Surface * screen);
	void map::drawRoadSelectron(SDL_Surface * screen);
	void map::drawBoard(SDL_Surface * screen);
	void map::handleInput(SDL_Event e, player * p);
	void map::constructRoadOnMap(player * p);
	void map::constructSettlementOnMap(player * p);
};