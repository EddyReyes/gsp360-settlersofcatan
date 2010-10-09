#include "map.h"

// THIS FILE IS STRICTLY USED FOR THE INITIALIZATION OF THE UNDERLYINGbOARD VARIABLE ON STARTUP

#define _EDGE(c,d) Edge(getNode(tempNodes, count, c),\
							getNode(tempNodes, count, d))

#define _CENTER(c,d,e) Center(getNode(tempNodes, count, c),\
							getNode(tempNodes, count, d), e)

map::map()
{
	//========PLACEHOLDER FOR FREE TWO ROADS AND FREE TWO RESOURCES.
	placeholderFREE = 2;

	//=========INIT TIME IN DVC
	dvc.initTimeDVC();

	//==========soundQueue
	soundQueue = 20;

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
		myNodes[i].owner = NOT_A_PLAYER;
		myNodes[i].cityType = 0;
	}

	for (int i = 0; i < 54; ++i)
	{
		setHarbor(&myNodes[i]);
		cout << i << '\t' << myNodes[i].harborType << endl;
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
	{
		myCenters[i] = tempCenters[i];
	}

	//=============CENTER GETTING NODES====================

	for(int i = 0; i < 19; ++i)
	{
		int allotedCenters = 0;
		for (int j = 0; j < 54; ++j)
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

	//============= CENTER PIXEL ASSIGNMENTS =================
	int centerPixelPlaceHolder = 0;
	for (int i = 0; i < 19; ++i)
	{
		if(i == 0 || i == 4 || i == 9 || i == 14 || i == 18)
		{
			centerPixelPlaceHolder = 0;
		}
		else if(i == 1 || i == 6 || i == 11 || i == 16)
		{
			centerPixelPlaceHolder = -32;
		}
		else if(i == 2 || i == 7 || i == 12 || i == 17)
		{
			centerPixelPlaceHolder = 32;
		}
		else if(i == 3 || i == 8 || i == 13)
		{
			centerPixelPlaceHolder = -64;
		}
		else if(i == 5 || i == 10 || i == 15)
		{
			centerPixelPlaceHolder = 64;
		}
		myCenters[i].pixelX = myCenters[i].x * (400 / 9) - centerPixelPlaceHolder - 19;
		myCenters[i].pixelY = myCenters[i].y * 50 - 19;
	}

	//=============EDGE ASSIGNMENT=========================

	int amountEdges = 0;

	Edge * tempEdges;

	tempEdges = new Edge [200];

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

	for (int i = 0; i < count; ++i)
	{
		myNodes[i].numOfEdges = myNodes[i].numOfEdges+myNodes[i].numOfEdges;
	}

	//cout << "TOTAL NUM OF EDGES == " << amountEdges << endl;

	for (int i = 0; i < count; ++i)
	{
		myNodes[i].setUnusedEdges();
	}


	const int eCount = amountEdges;

	for (int i = 0; i < eCount; ++i)
	{
		myEdges[i] = tempEdges[i];
		myEdges[i].ID = i;
		myEdges[i].owner = NOT_A_PLAYER; // 4 means player 5, and is treated as never.
		for (int j = 0; j < eCount; ++j)
		{
			if (myEdges[i].from == myEdges[j].to && myEdges[i].to == myEdges[j].from)
			{
				myEdges[i].sisterEdge = &myEdges[j];
				myEdges[i].sisterEdge->sisterEdge = &myEdges[i];
			}
		}
		myEdges[i].to->addNewEdge(&myEdges[i]);
		myEdges[i].from->addNewEdge(&myEdges[i]); 
	}

	delete tempEdges;

	//=========CHIT ASSIGNMENT=================

	int tempInts[] = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};
	for (int i = 0; i < 19; ++i)
	{
		myChits[i] = tempInts[i];
	}

	//=========IMAGE ASSIGNMENT==================

	initializeImages();

	//===========SELECTRON====================
	nodeSelectron = NULL;
	roadSelectron = NULL;
	centerSelectron = NULL;

	//============SETTING THE EDGES IN TERMS OF PIXELS=========================

	for (int i = 0; i < 144; ++i)
	{
		myEdges[i].pixelX = ( (myEdges[i].from->pixelX + myEdges[i].to->pixelX) / 2 );
		myEdges[i].pixelY = ( myEdges[i].from->pixelY + myEdges[i].to->pixelY ) / 2 ;
	}

	//=======DICE ROLL STUFF=================
	rolledDice = false;

	//=======TextMapImageStuff====================
	textColor.r = 255;//yellowish text for now 255,255,9
	textColor.g = 255;
	textColor.b = 9;

	font = NULL;
	resourceListMsg[0] = NULL;
	resourceListMsg[1] = NULL;
	resourceListMsg[2] = NULL;
	resourceListMsg[3] = NULL;
	resourceListMsg[4] = NULL;
	playerTag = NULL;

	//=============TradeBank Stuff================
	tradebank = new TradeBank;

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
	srand((unsigned int)time(0));
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
		if (selector < woodLeft){myCenters[i].resource = WOOD; myCenters[i].thiefHere = false; woodLeft--;}
		else if (selector < woodLeft + sheepLeft){myCenters[i].resource = SHEEP; myCenters[i].thiefHere = false;  sheepLeft--;}
		else if (selector < woodLeft + sheepLeft + brickLeft){myCenters[i].resource = BRICK; myCenters[i].thiefHere = false;  brickLeft--;}
		else if (selector < woodLeft + sheepLeft + brickLeft + stoneLeft){myCenters[i].resource = STONE; myCenters[i].thiefHere = false;  stoneLeft--;}
		else if (selector < woodLeft + sheepLeft + brickLeft + stoneLeft + wheatLeft){myCenters[i].resource = WHEAT; myCenters[i].thiefHere = false;  wheatLeft--;}
		else {myCenters[i].resource = 'D'; myCenters[i].thiefHere = true; desertLeft--;}
	}

	int tempInts[] = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};
	int tempIntCenters[] = {13, 16, 18, 17, 15, 10, 5, 2, 0, 1, 3, 8, 11, 14, 12, 7, 4, 6, 9};
	for (int i = 0; i < 19; ++i)
	{
		if (myCenters[tempIntCenters[i]].resource == 'D'){desertPass = 1; myCenters[tempIntCenters[i]].thiefHere = true; myCenters[tempIntCenters[i]].chitWorth = 0;}
		else {myCenters[tempIntCenters[i]].chitWorth = tempInts[i - desertPass];}
	}
}

char map::randomHarbor(int resource[])
{
	srand(0);
	int num;
	char type = ' ';
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
				switch(num)
				{
				case 0:
					type = SHEEP;
					break;
				case 1:
					type = WOOD;
					break;
				case 2:
					type = WHEAT;
					break;
				case 3:
					type = BRICK;
					break;
				case 4:
					type = STONE;
					break;
				}
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
				type = THREE_TO_ONE;
			}
			else
			{
				acceptable = false;
			}
		}
	}
	return type;
}

void map::setHarbor(Node* harbor)
{
	int resource[6] = {0, 0, 0, 0, 0, 0};
	char type = ' ';

	for(int i = 0; i < 54; i++)
	{
		//places harbor on pre-determined nodes
		
		switch(i)
		{
		case 2:
			type = randomHarbor(resource);
			harbor[i].harborType = type;
			break;
		case 3:
			harbor[i].harborType = harbor[2].harborType;
			break;
		case 4:
			type = randomHarbor(resource);
			harbor[i].harborType = type;
			break;
		case 5:
			harbor[i].harborType = harbor[4].harborType;
			break;
		case 6:
			type = randomHarbor(resource);
			harbor[i].harborType = type;
			break;
		case 12:
			harbor[i].harborType = harbor[6].harborType;
			break;
		case 11:
			type = randomHarbor(resource);
			harbor[i].harborType = type;
			break;
		case 17:
			harbor[i].harborType = harbor[11].harborType;
			break;
		case 24:
			type = randomHarbor(resource);
			harbor[i].harborType = type;
			break;
		case 30:
			harbor[i].harborType = harbor[24].harborType;
			break;
		case 29:
			type = randomHarbor(resource);
			harbor[i].harborType = type;
			break;
		case 35:
			harbor[i].harborType = harbor[29].harborType;
			break;
		case 43:
			type = randomHarbor(resource);
			harbor[i].harborType = type;
			break;
		case 49:
			harbor[i].harborType = harbor[43].harborType;
			break;
		case 46:
			type = randomHarbor(resource);
			harbor[i].harborType = type;
			break;
		case 51:
			harbor[i].harborType = harbor[46].harborType;
			break;
		case 52:
			type = randomHarbor(resource);
			harbor[i].harborType = type;
			break;
		case 53:
			harbor[i].harborType = harbor[52].harborType;
			break;
		default:
			harbor[i].harborType = NULL;
		}
		
	}
}

map::~map()
{
	delete tradebank;
	//delete font;//this gives s warning, but it builds
	//im not sure if we need to delete font though, or how to do it the right way
}