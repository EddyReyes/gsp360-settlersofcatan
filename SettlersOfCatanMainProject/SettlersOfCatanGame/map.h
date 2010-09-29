#pragma once

#include "sdl/sdl.h"
#include <iostream>
#include <ctime>
#include <windows.h>
#include "edge.h"
#include "node.h"
#include "center.h"
#include "stndrd.h"

using namespace std;

class map
{
private:
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
	void map::draw(SDL_Surface * screen);
	void map::loadImages(void);
	void map::shutdownImages(void);
};