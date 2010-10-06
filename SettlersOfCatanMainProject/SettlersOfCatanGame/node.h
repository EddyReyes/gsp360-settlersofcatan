#pragma once
#include "edge.h"
#include <iostream>
using namespace std;

class Center;
class Edge;

class Node
{
public:
	int ID;
	int harborType;
	int cityType;
	int owner;
	int x;
	int y; 
	int numOfEdges;
	int unusedEdges;
	char icon;
	Edge * nodeEdges[6];
	int pixelX;
	int pixelY;

	Node::Node(){};
	Node::Node(int a_x, int a_y, int a_ID)
	{
		x = a_x;
		y = a_y;
		icon = '@';
		numOfEdges = 0;
		unusedEdges = 0;
		ID = a_ID;
		cityType = 0;
		for (int i = 0; i < 6; ++i)
		{
			nodeEdges[i] = NULL;
		}
	}

	void Node::setEdgeCount(int a_numOfEdges)
	{
		numOfEdges = a_numOfEdges;
	}

	void Node::setUnusedEdges(void)
	{
		unusedEdges = numOfEdges;
	}

	void Node::addNewEdge(Edge * sentEdge)
	{
		nodeEdges[numOfEdges-unusedEdges] = sentEdge;
		unusedEdges--;
	}

	void Node::setEdge(int a_index, Edge * e)
	{
		nodeEdges[a_index] = e;
	}

	void Node::setNode(int a_x, int a_y, int a_ID)
	{
		x = a_x;
		y = a_y;
		icon = '@';
		numOfEdges = 0;
		ID = a_ID;
	}
};