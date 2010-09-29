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
	int whoHasARoadHere;
	//constructor
	Edge::Edge(Node * a_from, Node * a_to)
	{
		from = a_from;
		to = a_to;
		whoHasARoadHere = NULL;
	}

	void Edge::setEdgeFromAndTo(Node * a_from, Node * a_to)
	{
		this->from = a_from;
		this->to = a_to;
	}
};