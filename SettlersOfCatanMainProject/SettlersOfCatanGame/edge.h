#pragma once
#include "node.h"
#include "center.h"


class Node;
class Center;

class Edge
{
private:
public:
	Node * from;
	Node * to;
	Edge::Edge(){}
	int owner; // 0 through 3
	int ID;
	int pixelX;
	int pixelY;
	//constructor
	Edge::Edge(Node * a_from, Node * a_to)
	{
		from = a_from;
		to = a_to;
		owner = NULL;
	}

	void Edge::setEdgeFromAndTo(Node * a_from, Node * a_to)
	{
		from = a_from;
		to = a_to;
	}
};