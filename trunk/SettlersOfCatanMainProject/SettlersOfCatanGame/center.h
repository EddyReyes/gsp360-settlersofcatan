#pragma once
#include "node.h"
#include "edge.h"

class Node;
class Edge;

class Center
{
private:

public:
	int x;
	int y;
	int ID;
	char resource;
	int chitWorth;
	Node * connectedNodes[6];
	Center::Center(){};

	Center::Center(Node * from, Node * to, int a_ID)
	{
		x = (from->x + to->x) / 2;
		y = (from->y + to->y) / 2;
		ID = a_ID;
	}
};