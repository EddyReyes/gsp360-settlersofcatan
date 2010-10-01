#include "map.h"

#define _EDGE(c,d) Edge(getNode(tempNodes, count, c),\
							getNode(tempNodes, count, d))

#define _CENTER(c,d,e) Center(getNode(tempNodes, count, c),\
							getNode(tempNodes, count, d), e)




map::map()
{
	//=====NODE ASSIGNMENT==================
	int count;
	mapState = map::TURNONESETTLEMENT;
	overallTurn = 1;

	Node tempNodes[54] = {
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

	for(int i = 0; i < 54; ++i)
	{
		myNodes[i] = tempNodes[i];
		myNodes[i].owner = 4;
	}

	for (int i = 0; i < 54; ++i)
	{
		setHarbor(&myNodes[i]);
	}
		

	//===========SETTING THE NODES IN TERMS OF PIXELS=========================
	int x = 0;

	for (int i = 0; i < 54; ++i)
	{
		switch(myNodes[i].x)
		{
			case 8:		x = 0;		break;
			case 10:	x = 0;		break;
			case 7:		x = 24;		break;
			case 11:	x = -24;	break;
			case 4:		x = 48;		break;
			case 5:		x = 36;		break;
			case 13:	x = -36;	break;
			case 14:	x = -48;	break;
			case 16:	x = -64;	break;
			case 2:		x = 64;		break;
			case 17:	x = -96;	break;
			case 1:		x = 96;		break;
			default:	x = -200;	break;
		}
		myNodes[i].pixelX = myNodes[i].x * (400/9) - 16 + x;
		myNodes[i].pixelY = myNodes[i].y * 50 - 16;
	}

	count = 54;

	//========CENTER ASSIGNMENT==================

	Center tempCenters[19] = 
	{
						_CENTER(4, 5, 1),
				_CENTER(8, 9, 2),_CENTER(10, 11, 3),
		_CENTER(13, 14, 4),_CENTER(15, 16, 5),_CENTER(17, 18, 6),
				_CENTER(20, 21, 7),_CENTER(22, 23, 8),
		_CENTER(25, 26, 9),_CENTER(27, 28, 10),_CENTER(29, 30, 11),
				_CENTER(32, 33, 12),_CENTER(34, 35, 13),
		_CENTER(37, 38, 14),_CENTER(39, 40, 15),_CENTER(41, 42, 16),
				_CENTER(44, 45, 17),_CENTER(46, 47, 18),
						_CENTER(50, 51, 19),
	};

	for(int i = 0; i < 19; ++i)
		myCenters[i] = tempCenters[i];

	//=============CENTER GETTING NODES====================

	for(int i = 0; i < 19; ++i)
	{
		int allotedCenters = 0;
		for (int j = 0; j < 54; j++)
		{
			if (myNodes[j].y == myCenters[i].y)
			{
				if (myNodes[j].x + 2 == myCenters[i].x ||
					myNodes[j].x - 2 == myCenters[i].x)
				{
					myCenters[i].connectedNodes[allotedCenters] = &myNodes[j];
					allotedCenters++;
				}
			}
			else if (myNodes[j].y + 1 == myCenters[i].y)
			{
				if (myNodes[j].x + 1 == myCenters[i].x ||
					myNodes[j].x - 1 == myCenters[i].x)
				{
					myCenters[i].connectedNodes[allotedCenters] = &myNodes[j];
					allotedCenters++;
				}
			}
			else if (myNodes[j].y - 1 == myCenters[i].y)
			{
				if (myNodes[j].x + 1 == myCenters[i].x ||
					myNodes[j].x - 1 == myCenters[i].x)
				{
					myCenters[i].connectedNodes[allotedCenters] = &myNodes[j];
					allotedCenters++;
				}
			}
		}
	}

	//=============EDGE ASSIGNMENT=========================

	int amountEdges = 0;

	Edge * tempEdges;

	tempEdges = new Edge [1000];

	for(int i = 0; i < count; ++i)
	{
		for(int j = 0; j < count; ++j)
		{
			if(j != i)
			{

				if ((myNodes[i].y) == (myNodes[j].y) || // all these / scale
					(myNodes[i].y) + 1 == (myNodes[j].y) ||
					(myNodes[i].y) - 1 == (myNodes[j].y) )
				{
					if( (myNodes[i].x) + 2 == (myNodes[j].x) || //ALL THESE / scale
						(myNodes[i].x) + 1 == (myNodes[j].x) ||
						(myNodes[i].x) - 2 == (myNodes[j].x) ||
						(myNodes[i].x) - 1 == (myNodes[j].x) )
					{
						getNode(myNodes,count, i + 1)->numOfEdges++;
						tempEdges[amountEdges].from = getNode(myNodes, count, i + 1);
						tempEdges[amountEdges].to = getNode(myNodes, count, j + 1);
						amountEdges++;
					}
				}
			}
		}
	}


	const int eCount = amountEdges;

	for (int i = 0; i < eCount; ++i)
	{
		myEdges[i] = tempEdges[i];
		myEdges[i].ID = i;
		myEdges[i].owner = 4; // 4 means player 5, and is treated as never.
		myEdges[i].to->addNewEdge(&myEdges[i]); //cout << "called function 2" << endl;
		myEdges[i].from->addNewEdge(&myEdges[i]); //cout << "called function" << endl;
	}

	delete tempEdges;

	//=========CHIT ASSIGNMENT=================

	int tempInts[] = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};
	for (int i = 0; i < 19; ++i)
	{
		myChits[i] = tempInts[i];
	}

	//=========IMAGE ASSIGNMENT==================

	resourceCard = NULL;
	buildCard = NULL;
	testSelect = NULL;
	hexTile = NULL;
	woodTile = NULL;
	wheatTile = NULL;
	stoneTile = NULL;
	sheepTile = NULL;
	brickTile = NULL;
	for (int i = 0; i < 10; ++i)
	{
		chitTile[i] = NULL;
	}
	for (int i = 0; i < 4; ++i)
	{
		settlementTile[i] = NULL;
		cityTile[i] = NULL;
		roadTile[i] = NULL;
	}

	//===========SELECTRON====================
	nodeSelectron = NULL;
	roadSelectron = NULL;

	//============SETTING THE EDGES IN TERMS OF PIXELS=========================

	for (int i = 0; i < 144; ++i)
	{
		myEdges[i].pixelX = ( (myEdges[i].from->pixelX + myEdges[i].to->pixelX) / 2 );
		myEdges[i].pixelY = ( myEdges[i].from->pixelY + myEdges[i].to->pixelY ) / 2 ;
	}

}

Node * map::getNode(Node * population, int popCount, int ID)
{
	for(int i = 0; i < popCount; i++)
		if(population[i].ID == ID)
			return &population[i];
	return 0;
}

int map::getEdge(Edge * population, int popCount, int start, Node * from)
{
	for(int i = start; i < popCount; ++i)
		if(population[i].from == from)
			return i;
	return -1;
}

int map::getEdgeFromCount(Edge * population, int popCount, Node * from)
{
	int count =0;
	for(int i = 0; i < popCount; ++i)
		if(population[i].from == from)
			count++;
	return count;
}


void map::initializeCenters(void)
{
	srand(time(0));
	rand();
	int woodLeft = 4;
	int stoneLeft = 3;
	int brickLeft = 3;
	int wheatLeft = 4;
	int sheepLeft = 4;
	int desertLeft = 1;
	int selector = 0;
	int desertPass = 0;
	// SELECTS A RANDOM NUMBER OUT OF ALL THE REMAINING AVAILABLE TILES AND ASSIGNS RESOURCES. INCLUDING 'D', DESERT
	for (int i = 0; i < 19; i++)
	{
		selector = rand();
		selector = selector % (woodLeft + sheepLeft + brickLeft + stoneLeft + wheatLeft + desertLeft);
		if (selector < woodLeft){myCenters[i].resource = WOOD; woodLeft--;}
		else if (selector < woodLeft + sheepLeft){myCenters[i].resource = SHEEP; sheepLeft--;}
		else if (selector < woodLeft + sheepLeft + brickLeft){myCenters[i].resource = BRICK; brickLeft--;}
		else if (selector < woodLeft + sheepLeft + brickLeft + stoneLeft){myCenters[i].resource = STONE; stoneLeft--;}
		else if (selector < woodLeft + sheepLeft + brickLeft + stoneLeft + wheatLeft){myCenters[i].resource = WHEAT; wheatLeft--;}
		else {myCenters[i].resource = 'D'; desertLeft--;}
	}

	int tempInts[] = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};
	int tempIntCenters[] = {13, 16, 18, 17, 15, 10, 5, 2, 0, 1, 3, 8, 11, 14, 12, 7, 4, 6, 9};
	for (int i = 0; i < 19; ++i)
	{
		if (myCenters[tempIntCenters[i]].resource == 'D'){desertPass = 1; myCenters[tempIntCenters[i]].chitWorth = 0;}
		else {myCenters[tempIntCenters[i]].chitWorth = tempInts[i - desertPass];}
	}
}

int map::randomHarbor(int resource[])
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

void map::setHarbor(Node* harbor)
{
	int num, resource[6] = {0, 0, 0, 0, 0, 0};

	for(int i = 0; i < 54; i++)
	{
		//places harbor on pre-determined nodes
		/*
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
		*/
	}
}

void map::whichNodeIsWithin(int const & x, int const & y, int radius)
{
	float minDistance, distance, dx, dy, maxRadius = radius*radius;
	minDistance = 2500;
	Node * closest = NULL;
	for(int i = 0; i < 54; ++i)
	{
		dx = myNodes[i].pixelX + 16- x;
		dy = myNodes[i].pixelY + 16 - y;
		distance = dx*dx + dy*dy;
		if(distance < maxRadius 
		&& (closest != NULL || distance < minDistance))
		{
			minDistance = distance;
			nodeSelectron = myNodes[i].ID - 1;
		}
	}
}

void map::whichRoadIsWithin(int const & x, int const & y, int radius)
{
	float minDistance, distance, dx, dy, maxRadius = radius*radius;
	minDistance = 2500;
	Edge * closest = NULL;
	for(int i = 0; i < 144; ++i)
	{
		dx = myEdges[i].pixelX + 16 - x;
		dy = myEdges[i].pixelY + 16 - y;
		distance = dx*dx + dy*dy;
		if(distance < maxRadius 
		&& (closest != NULL || distance < minDistance))
		{
			minDistance = distance;
			roadSelectron = myEdges[i].ID;
		}
	}
}

bool map::constructRoadOnMap(player * p)
{
	bool buildable = false;

	if (myEdges[roadSelectron].owner == 4)
	{
		//cout << "got to 1" << endl;
		if (myEdges[roadSelectron].from->owner == p->ID || myEdges[roadSelectron].to->owner == p->ID)
		{
			buildable = true;
			//cout << "got to 2b (FINISH)" << endl;
		}
		else if ( myEdges[roadSelectron].to->owner == 4)
		{
			//cout << "got to 2a" << endl;
			for (int i = 0; i < myEdges[roadSelectron].to->numOfEdges; ++i)
			{
				//cout << "got to 3a" << endl;
				if (myEdges[roadSelectron].to->nodeEdges[i]->owner == p->ID)
				{
					//cout << "got to 4a FINISH" << endl;
					buildable = true;
				}
			}
		}
		else if ( myEdges[roadSelectron].from->owner == 4)
		{
			//cout << "got to 2c" << endl;
			for (int i = 0; i < myEdges[roadSelectron].to->numOfEdges; ++i)
			{
				//cout << "got to 3c" << endl;
				if (myEdges[roadSelectron].from->nodeEdges[i]->owner == p->ID)
				{
					//cout << "got to 4c FINISH" << endl;
					buildable = true;
				}
			}
		}
		
		
		if (buildable == true)
		{
			//cout << "got to BUILD!" << endl;
			myEdges[roadSelectron].owner = p->ID;
			return true;
		}
	}
	return false;
}

bool map::constructSettlementOnMap(player * p)
{
	//THIS FUNCTION IS MILDLY BAD. IT LOOKS FOR BUILDABILITY BY DRAW PIXEL COUNTS, NOT BY ACTUALLY LOOKING AT EDGES THAT CONNECT TO NODES.
	bool buildable = false;
	for (int i = 0; i < 54; ++i)
	{
		if (nodeSelectron != i)
		{
			if (myNodes[i].owner != 4)
			{
				if							(!(

					((myNodes[i].x + 1 == myNodes[nodeSelectron].x ||
					myNodes[i].x - 1 == myNodes[nodeSelectron].x) 
											&&
					(myNodes[i].y + 1 == myNodes[nodeSelectron].y ||
					myNodes[i].y - 1 == myNodes[nodeSelectron].y)) 
					
											&&


					((myNodes[i].x + 2 == myNodes[nodeSelectron].x ||
					myNodes[i].x - 2 == myNodes[nodeSelectron].x)
											&&
					(myNodes[i].y == myNodes[nodeSelectron].y))
					
											))
				{
					buildable = true;
				}
			}
		}
	}
	// RIGHT AROUND HERE, THIS FUNCTION WOULD NEED TO CHECK FOR ROADS AND SET BUILDABILITY TO FALSE IF IT FINDS NONE.

	for (int i = 0; myNodes[nodeSelectron].numOfEdges; ++i)
	{
		if (myNodes[nodeSelectron].nodeEdges[i]->owner == p->ID)
		{
			buildable = true;
		}
	}

	if (buildable == true && myNodes[nodeSelectron].owner == 4)
	{
		myNodes[nodeSelectron].owner = p->ID;
		myNodes[nodeSelectron].cityType = 1;
		return true;
	}
	return false;
}

bool map::constructSettlementOnMapAnywhere(player * p)
{
	bool buildable = true;
	for (int i = 0; i < 54; ++i)
	{
		if (nodeSelectron != i)
		{
			if (myNodes[i].owner != 4)
			{
				if							(

					((myNodes[i].x + 1 == myNodes[nodeSelectron].x ||
					myNodes[i].x - 1 == myNodes[nodeSelectron].x) 
											&&
					(myNodes[i].y + 1 == myNodes[nodeSelectron].y ||
					myNodes[i].y - 1 == myNodes[nodeSelectron].y)) 
					
											||


					((myNodes[i].x + 2 == myNodes[nodeSelectron].x ||
					myNodes[i].x - 2 == myNodes[nodeSelectron].x)
											&&
					(myNodes[i].y == myNodes[nodeSelectron].y))
					
											)
				{
					buildable = false;
				}
			}
		}
	}
	if (buildable == true && myNodes[nodeSelectron].owner == 4)
	{
		myNodes[nodeSelectron].owner = p->ID;
		myNodes[nodeSelectron].cityType = 1;
		return true;
	}
	return false;
}