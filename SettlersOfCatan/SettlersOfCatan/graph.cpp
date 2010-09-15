#include <iostream>
#include <ctime>
#include <windows.h>

#include "player.h"

using namespace std;

//set cursor to location
void gotoxy(int x, int y)
{
	COORD position = {x, y};
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		position);
}

struct harborType;

struct Edge;

struct Node
{
	int ID, harborType, x, y, numOfEdges;
	char icon;
	Edge ** edges;

	Node(int a_x, int a_y, int a_ID)
	{
		x = a_x * 3;
		y = a_y * 3;
		icon = '@';
		edges = 0;
		numOfEdges = 0;
		ID = a_ID;
	}

	void print()
	{
		gotoxy(x, y);
		cout << icon << ID;
	}

	void setEdgeCount(int a_numOfEdges)
	{
		if(edges)
			delete edges;
		numOfEdges = a_numOfEdges;
		edges = new Edge * [numOfEdges];
	}

	void setEdge(int a_index, Edge * e)
	{
		edges[a_index] = e;
	}
};

struct Edge
{
	Node * from;
	Node * to;
	//player * whoHasARoadHere;

	//constructor
	Edge(Node * a_from, Node * a_to)
	{
		from = a_from;
		to = a_to;
	}

	//prints edge to screen
	void print()
	{
						//set midpoint
		int avgX = (from->x*2 + to->x)/3,
			avgY = (from->y*2 + to->y)/3;

		gotoxy(avgX, avgY);
		cout << from->icon << to->icon;
	}
};

Node * getNode(Node * population, int popCount, int ID)
{
	for(int i = 0; i < popCount; i++)
		if(population[i].ID == ID)
			return &population[i];
	return 0;
}

int getEdge(Edge * population, int popCount, int start, Node * from)
{
	for(int i = start; i < popCount; ++i)
		if(population[i].from == from)
			return i;
	return -1;
}

int getEdgeFromCount(Edge * population, int popCount, Node * from)
{
	int count =0;
	for(int i = 0; i < popCount; ++i)
		if(population[i].from == from)
			count++;
	return count;
}

int randomHarbor(int resource[])
{
	srand(0);
	int num;
	bool acceptable = false;

	//determine if the harbor has already been placed
	while(acceptable != true)
	{
		num = (rand() % 6);
		if(num < 5)
		{
			if(resource[num] < 1)
			{
				acceptable = true;
				resource[num]++;
			}
			else
			{
				acceptable = false;
			}
		}
		else
		{
			if(resource[num] < 5)
			{
				resource[num]++;
				acceptable = true;
			}
			else
			{
				acceptable = false;
			}
		}
	}
	return num;
}

void setHarbor(Node* harbor)
{
	int num, resource[6] = {0, 0, 0, 0, 0, 0};

	for(int i = 0; i < 54; i++)
	{
		//places harbor on pre-determined nodes
		switch(i)
		{
		case 2:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 3:
			harbor[i].harborType = harbor[2].harborType;
			break;
		case 4:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 5:
			harbor[i].harborType = harbor[4].harborType;
			break;
		case 6:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 12:
			harbor[i].harborType = harbor[6].harborType;
			break;
		case 11:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 17:
			harbor[i].harborType = harbor[11].harborType;
			break;
		case 24:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 30:
			harbor[i].harborType = harbor[24].harborType;
			break;
		case 29:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 35:
			harbor[i].harborType = harbor[29].harborType;
			break;
		case 43:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 49:
			harbor[i].harborType = harbor[43].harborType;
			break;
		case 46:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 51:
			harbor[i].harborType = harbor[46].harborType;
			break;
		case 52:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 53:
			harbor[i].harborType = harbor[52].harborType;
			break;
		default:
			harbor[i].harborType = NULL;
		}
	}
}

#define _EDGE(c,d) Edge(getNode(myNodes, count, c),\
							getNode(myNodes, count, d))

void main()
{
	//set node values
	Node myNodes[] = 
	{
							 	 Node(8,1,1),Node(10,1,2),
					 Node(5,2,3),Node(7,2,4),Node(11,2,5),Node(13,2,6),
		 Node(2,3,7),Node(4,3,8),Node(8,3,9),Node(10,3,10),Node(14,3,11),Node(16,3,12),
		Node(1,4,13),Node(5,4,14),Node(7,4,15),Node(11,4,16),Node(13,4,17),Node(17,4,18),
		 Node(2,5,19),Node(4,5,20),Node(8,5,21),Node(10,5,22),Node(14,5,23),Node(16,5,24),
		Node(1,6,25),Node(5,6,26),Node(7,6,27),Node(11,6,28),Node(13,6,29),Node(17,6,30),
		 Node(2,7,31),Node(4,7,32),Node(8,7,33),Node(10,7,34),Node(14,7,35),Node(16,7,36),
		Node(1,8,37),Node(5,8,38),Node(7,8,39),Node(11,8,40),Node(13,8,41),Node(17,8,42),
		 Node(2,9,43),Node(4,9,44),Node(8,9,45),Node(10,9,46),Node(14,9,47),Node(16,9,48),
					 Node(5,10,49),Node(7,10,50),Node(11,10,51),Node(13,10,52),
								 Node(8,11,53),Node(10,11,54),
	};

	//find number of nodes
	const int count = sizeof(myNodes) / sizeof(Node);

	//print each node
	for(int i = 0; i < count; ++i)
	{
		myNodes[i].print();
	}

	Edge myEdges[] =
	{
		_EDGE(1,2),_EDGE(2,5),
	};

	const int eCount = sizeof(myEdges) / sizeof(Edge);

	for(int i = 0; i < eCount; ++i)
	{
		myEdges[i].print();
	}

	setHarbor(myNodes);

	cout << endl << endl;
}