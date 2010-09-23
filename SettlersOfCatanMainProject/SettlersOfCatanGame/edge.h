#pragma once
#include "node.h"
#include "center.h"

class Node;
class Center;

class Edge
{
private:
	//player * whoHasARoadHere;
public:
	Node * from;
	Node * to;
	Edge::Edge(){}
	//constructor
	Edge::Edge(Node * a_from, Node * a_to)
	{
		from = a_from;
		to = a_to;
	}

	//prints edge to screen
	void Edge::print()
	{
						//set midpoint
		/*
		int avgX = (from->x*2 + to->x)/3,
			avgY = (from->y*2 + to->y)/3;
			*/
		int avgX = (from->x + to->x) / 2,
			avgY = (from->y + to->y) / 2;

		//gotoxy(avgX, avgY);
		//cout << from->icon << to->icon;
	}
	void Edge::setEdgeFromAndTo(Node * a_from, Node * a_to)
	{
		this->from = a_from;
		this->to = a_to;
	}
};