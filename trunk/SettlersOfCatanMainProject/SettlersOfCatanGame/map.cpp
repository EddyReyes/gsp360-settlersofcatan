#include "map.h"
#include "stndrd.h"
#include <ctime>
#include <windows.h>

#define _EDGE(c,d) Edge(getNode(tempNodes, count, c),\
							getNode(tempNodes, count, d))

#define _CENTER(c,d,e) Center(getNode(tempNodes, count, c),\
							getNode(tempNodes, count, d), e)

map::map()
{
	int count;

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
		myNodes[i] = tempNodes[i];

	count = 54;

	Center tempCenters[19] = 
	{
						_CENTER(4, 5, 1),
				_CENTER(8, 9, 2),_CENTER(10, 11, 3),
		_CENTER(13, 14, 4),_CENTER(15, 16, 5),_CENTER(17, 18, 6),
		_CENTER(20, 21, 7),
		_CENTER(22, 23, 8),
		_CENTER(25, 26, 9),
		_CENTER(27, 28, 10),
		_CENTER(29, 30, 11),
				_CENTER(32, 33, 12),_CENTER(34, 35, 13),
		_CENTER(37, 38, 14),_CENTER(39, 40, 15),_CENTER(41, 42, 16),
				_CENTER(44, 45, 17),_CENTER(46, 47, 18),
						_CENTER(50, 51, 19),
	};

	for(int i = 0; i < 19; ++i)
		myCenters[i] = tempCenters[i];

	//=================EDGEFINDER==============================================================

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
						getNode(tempNodes,count, i + 1)->numOfEdges++;
						tempEdges[amountEdges].from = getNode(tempNodes, count, i + 1);
						tempEdges[amountEdges].to = getNode(tempNodes, count, j + 1);
						amountEdges++;
					}
				}
			}
		}
	}


	const int eCount = amountEdges;

	for (int i = 0; i < eCount; ++i)
	{
		myEdges[i].setEdgeFromAndTo(tempEdges[i].from, tempEdges[i].to);
	}

	delete tempEdges;

	//=============================================END OF EDGEFINDER=================================

	int tempInts[] = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};
	for (int i = 0; i < 19; ++i)
	{
		myChits[i] = tempInts[i];
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

	// THIS SECTION IS BIZARRE 
	// IN ORDER TO ASSIGN CHIT WORTH THESE COMMANDS HAVE TO BE REPEATED OVER AND OVER AGAIN.
	// A FOR LOOP CAN'T EXIST DUE TO THE PATTERN WE HAVE FOR NAMING CENTERS. 13 -> 16 -> 18 is bottom left, middle bottom left, bottom, etc.
	myCenters[13].chitWorth = myChits[0 - desertPass];
	if (myCenters[13].resource == 'D'){desertPass = 1; myCenters[13].chitWorth = 0;}
	myCenters[16].chitWorth = myChits[1 - desertPass];
	if (myCenters[16].resource == 'D'){desertPass = 1; myCenters[16].chitWorth = 0;}
	myCenters[18].chitWorth = myChits[2 - desertPass];
	if (myCenters[18].resource == 'D'){desertPass = 1; myCenters[18].chitWorth = 0;}
	myCenters[17].chitWorth = myChits[3 - desertPass];
	if (myCenters[17].resource == 'D'){desertPass = 1; myCenters[17].chitWorth = 0;}
	myCenters[15].chitWorth = myChits[4 - desertPass];
	if (myCenters[15].resource == 'D'){desertPass = 1; myCenters[15].chitWorth = 0;}
	myCenters[10].chitWorth = myChits[5 - desertPass];
	if (myCenters[10].resource == 'D'){desertPass = 1; myCenters[18].chitWorth = 0;}
	myCenters[5].chitWorth = myChits[6 - desertPass];
	if (myCenters[5].resource == 'D'){desertPass = 1; myCenters[5].chitWorth = 0;}
	myCenters[2].chitWorth = myChits[7 - desertPass];
	if (myCenters[2].resource == 'D'){desertPass = 1; myCenters[2].chitWorth = 0;}
	myCenters[0].chitWorth = myChits[8 - desertPass];
	if (myCenters[0].resource == 'D'){desertPass = 1; myCenters[0].chitWorth = 0;}
	myCenters[1].chitWorth = myChits[9 - desertPass];
	if (myCenters[1].resource == 'D'){desertPass = 1; myCenters[1].chitWorth = 0;}
	myCenters[3].chitWorth = myChits[10 - desertPass];
	if (myCenters[3].resource == 'D'){desertPass = 1; myCenters[3].chitWorth = 0;}
	myCenters[8].chitWorth = myChits[11 - desertPass];
	if (myCenters[8].resource == 'D'){desertPass = 1; myCenters[8].chitWorth = 0;}
	myCenters[11].chitWorth = myChits[12 - desertPass];
	if (myCenters[11].resource == 'D'){desertPass = 1; myCenters[11].chitWorth = 0;}
	myCenters[14].chitWorth = myChits[13 - desertPass];
	if (myCenters[14].resource == 'D'){desertPass = 1; myCenters[14].chitWorth = 0;}
	myCenters[12].chitWorth = myChits[14 - desertPass];
	if (myCenters[12].resource == 'D'){desertPass = 1; myCenters[12].chitWorth = 0;}
	myCenters[7].chitWorth = myChits[15 - desertPass];
	if (myCenters[7].resource == 'D'){desertPass = 1; myCenters[7].chitWorth = 0;}
	myCenters[4].chitWorth = myChits[16 - desertPass];
	if (myCenters[4].resource == 'D'){desertPass = 1; myCenters[4].chitWorth = 0;}
	myCenters[6].chitWorth = myChits[17 - desertPass];
	if (myCenters[6].resource == 'D'){desertPass = 1; myCenters[6].chitWorth = 0;}
	// THIS LAST ONE WILL BREAK IF THE FUNCTION ASSIGNS THE DESERT TO IT AND CHECK DOES NOT HAPPEN TWICE. CLEAN IT UP LATER?
	if (myCenters[9].resource == 'D'){desertPass = 1; myCenters[9].chitWorth = 0;}
	myCenters[9].chitWorth = myChits[18 - desertPass];
	if (myCenters[9].resource == 'D'){desertPass = 1; myCenters[9].chitWorth = 0;}
}