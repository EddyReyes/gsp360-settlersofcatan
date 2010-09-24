#pragma once
//#include "center.h"
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
		x = a_x ;//* scale;
		y = a_y ;//* scale;
		icon = '@';
		edges = 0;
		numOfEdges = 0;
		ID = a_ID;
		cityType = 0;
	}

	/*
	void Node::print()
	{
		gotoxy(x, y);
		cout << 'N' << ID;
	}
	*/

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
		x = a_x; // * scale (if necessary)
		y = a_y; // * scale (if necessary)
		icon = '@';
		edges = 0;
		numOfEdges = 0;
		ID = a_ID;
	}
};