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
	char icon;
	Edge * nodeEdges[3];
	//Edge * tempEdges;
	int pixelX;
	int pixelY;

	Node::Node(){};
	Node::Node(int a_x, int a_y, int a_ID)
	{
		x = a_x;
		y = a_y;
		icon = '@';
		numOfEdges = 0;
		ID = a_ID;
		cityType = 0;
	}

	void Node::setEdgeCount(int a_numOfEdges)
	{
		numOfEdges = a_numOfEdges;
	}

	void Node::addNewEdge(Edge * sentEdge)
	{
		int j = 0;
		for (int i = 0; i < 3; ++i)
		{
			if (nodeEdges[i] == NULL)
			{
				j = i;
				break;
			}
		}
		nodeEdges[j] = sentEdge;
		numOfEdges = j++;
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
		//nodeEdges = NULL;
		numOfEdges = 0;
		ID = a_ID;
	}
};