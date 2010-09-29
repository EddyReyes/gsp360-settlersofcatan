#pragma once
#include "edge.h"

class Center;
class Edge;

class Node
{
public:
	int ID;
	int harborType;
	int cityType;
	int x;
	int y; 
	int numOfEdges;
	char icon;
	Edge ** edges;

	Node::Node(){};
	Node::Node(int a_x, int a_y, int a_ID)
	{
		x = a_x ;
		y = a_y ;
		icon = '@';
		edges = 0;
		numOfEdges = 0;
		ID = a_ID;
		cityType = 0;
	}

	void Node::setEdgeCount(int a_numOfEdges)
	{
		if(edges)
			delete edges;
		numOfEdges = a_numOfEdges;
		edges = new Edge * [numOfEdges];
	}

	void Node::setEdge(int a_index, Edge * e)
	{
		edges[a_index] = e;
	}

	void Node::setNode(int a_x, int a_y, int a_ID)
	{
		x = a_x;
		y = a_y;
		icon = '@';
		edges = 0;
		numOfEdges = 0;
		ID = a_ID;
	}
};