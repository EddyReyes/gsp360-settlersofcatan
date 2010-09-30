#include "map.h"

#define _EDGE(c,d) Edge(getNode(tempNodes, count, c),\
							getNode(tempNodes, count, d))

#define _CENTER(c,d,e) Center(getNode(tempNodes, count, c),\
							getNode(tempNodes, count, d), e)

map::map()
{
	//=====NODE ASSIGNMENT==================
	int count;
	mapState = map::MAP;

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

	//=====CENTER ASSIGNMENT==================

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

	//=======CHIT ASSIGNMENT=================

	int tempInts[] = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};
	for (int i = 0; i < 19; ++i)
	{
		myChits[i] = tempInts[i];
	}

	//=====IMAGE ASSIGNMENT==================

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

	//======SELECTRON====================
	nodeSelectron = NULL;
	roadSelectron = NULL;


	//=======SETTING THE NODES IN TERMS OF PIXELS
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

	int tempInts[] = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};
	int tempIntCenters[] = {13, 16, 18, 17, 15, 10, 5, 2, 0, 1, 3, 8, 11, 14, 12, 7, 4, 6, 9};
	for (int i = 0; i < 19; ++i)
	{
		if (myCenters[tempIntCenters[i]].resource == 'D'){desertPass = 1; myCenters[tempIntCenters[i]].chitWorth = 0;}
		else {myCenters[tempIntCenters[i]].chitWorth = tempInts[i - desertPass];}
	}
}

void map::loadImages()
{
	testSelect = load_image( "testSelector.bmp" );
	hexTile = load_image( "Hex_One.bmp" );
	woodTile = load_image( "WoodHex.bmp" );
	wheatTile = load_image( "WheatHex.bmp" );
	stoneTile = load_image( "StoneHex.bmp" );
	sheepTile = load_image( "SheepHex.bmp" );
	brickTile = load_image( "BrickHex.bmp" );
	chitTile[0] = load_image( "chit2.bmp" );
	chitTile[1] = load_image( "chit3.bmp" );
	chitTile[2] = load_image( "chit4.bmp" );
	chitTile[3] = load_image( "chit5.bmp" );
	chitTile[4] = load_image( "chit6.bmp" );
	chitTile[5] = load_image( "chit8.bmp" );
	chitTile[6] = load_image( "chit9.bmp" );
	chitTile[7] = load_image( "chit10.bmp" );
	chitTile[8] = load_image( "chit11.bmp" );
	chitTile[9] = load_image( "chit12.bmp" );
}
void map::drawNodeSelectron(SDL_Surface * screen)
{
	if (nodeSelectron >= 0 && nodeSelectron <= 53)
	{
		apply_surface(	myNodes[nodeSelectron].pixelX,
						myNodes[nodeSelectron].pixelY,
						testSelect,
						screen,
						NULL );
	}
}

void map::drawRoadSelectron(SDL_Surface * screen)
{

}


void map::drawBoard(SDL_Surface * screen)
{
	int x = 0;
	for (int i = 0; i < 19; ++i)
	{
		if(i == 0 || i == 4 || i == 9 || i == 14 || i == 18)
		{
			x = 64;
		}
		else if(i == 1 || i == 6 || i == 11 || i == 16)
		{
			x = 32;
		}
		else if(i == 2 || i == 7 || i == 12 || i == 17)
		{
			x = 96;
		}
		else if(i == 3 || i == 8 || i == 13)
		{
			x = 0;
		}
		else if(i == 5 || i == 10 || i == 15)
		{
			x = 128;
		}
		switch(myCenters[i].resource)
		{
		case WOOD:		apply_surface(	myCenters[i].x * (400 / 9) - x,
										myCenters[i].y * 50 - 55,
										woodTile,
										screen,
										NULL); break;
		case WHEAT:		apply_surface(	myCenters[i].x * (400 / 9) - x,
										myCenters[i].y * 50 - 55,
										wheatTile,
										screen,
										NULL); break;
		case STONE:		apply_surface(	myCenters[i].x * (400 / 9) - x,
										myCenters[i].y * 50 - 55,
										stoneTile,
										screen,
										NULL); break;
		case SHEEP:		apply_surface(	myCenters[i].x * (400 / 9) - x,
										myCenters[i].y * 50 - 55,
										sheepTile,
										screen,
										NULL); break;
		case BRICK:		apply_surface(	myCenters[i].x * (400 / 9) - x,
										myCenters[i].y * 50 - 55,
										brickTile,
										screen,
										NULL); break;
		case 'D':		apply_surface(	myCenters[i].x * (400 / 9) - x,
										myCenters[i].y * 50 - 55,
										hexTile,
										screen,
										NULL); break;
		}
	}
	x = 0;
	for (int i = 0; i < 19; ++i)
	{
		if(i == 0 || i == 4 || i == 9 || i == 14 || i == 18)
		{
			x = 0;
		}
		else if(i == 1 || i == 6 || i == 11 || i == 16)
		{
			x = -32;
		}
		else if(i == 2 || i == 7 || i == 12 || i == 17)
		{
			x = 32;
		}
		else if(i == 3 || i == 8 || i == 13)
		{
			x = -64;
		}
		else if(i == 5 || i == 10 || i == 15)
		{
			x = 64;
		}
		int y = 2;
		if(myCenters[i].chitWorth >= 8){ ++y; }
		if(myCenters[i].chitWorth != 0)
		{
			apply_surface(	myCenters[i].x * (400 / 9) - x - 19,
							myCenters[i].y * 50 - 19,
							chitTile[myCenters[i].chitWorth - y],
							screen,
							NULL);
		}
	}
}


void map::drawBuildCard(SDL_Surface * screen)
{

}

void map::drawResourceList(SDL_Surface * screen, player * p)
{

}

void map::drawDevHand(SDL_Surface * screen)
{

}

void map::drawTradeScreen(SDL_Surface * screen)
{

}

void map::draw(SDL_Surface * screen, player * p)
{
	switch(mapState)
	{
		case map::MAP:				drawBoard(screen);				
									drawNodeSelectron(screen);		break; // DELETE THE DRAW NODE SELECTRON FROM THIS PART, ITS ONLY FOR SHOW
		case map::BUILDCARD:		drawBuildCard(screen);			break;
		case map::RESOURCELIST:		drawResourceList(screen, p);	break;
		case map::DEVHAND:			drawDevHand(screen);			break;
		case map::TRADE:			drawTradeScreen(screen);		break;
		case map::BUILDROAD:		drawBoard(screen);
									drawRoadSelectron(screen);		break;
		case map::BUILDSETTLEMENT:	drawBoard(screen);
									drawNodeSelectron(screen);		break;
		case map::BUILDCITY:		drawBoard(screen);
									drawNodeSelectron(screen);		break;
	}
}

void map::shutdownImages()
{
	SDL_FreeSurface(testSelect);
	SDL_FreeSurface(hexTile);
	SDL_FreeSurface(woodTile);
	SDL_FreeSurface(wheatTile);
	SDL_FreeSurface(stoneTile);
	SDL_FreeSurface(sheepTile);
	SDL_FreeSurface(brickTile);
	for (int i = 0; i < 10; ++i)
	{
		SDL_FreeSurface(chitTile[i]);
	}
}

//function to load images
SDL_Surface* map::load_image( std::string filename ) 
{ 
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;
	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;
	
	//Load the image
	loadedImage = SDL_LoadBMP( filename.c_str() ); 

	//If nothing went wrong in loading the image
	if( loadedImage != NULL ) 
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );
		//Free the old image
		SDL_FreeSurface( loadedImage );
		if (optimizedImage != NULL)
		{
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xC0, 0xC0, 0xC0 ); //GRAYSCALE COLOR KEY ( 192, 192, 192 )
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
		}
	} 
//Return the optimized image
return optimizedImage;
}

void map::apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect* clip = NULL) 
{ 
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface( source, clip, destination, &offset ); 
}

void map::handleInput(SDL_Event e, player * p)
{
	switch(e.type)
	{
	case SDL_KEYDOWN:
		switch(e.key.keysym.sym)
		{
		case SDLK_1:	mapState= map::MAP;				break;
		case SDLK_2:	mapState= map::BUILDCARD;		break;
		case SDLK_3:	mapState= map::RESOURCELIST;	break;
		case SDLK_4:	mapState= map::DEVHAND;			break;
		case SDLK_5:	mapState= map::TRADE;			break;
		}
	case SDL_MOUSEMOTION:
		{
			whichNodeIsWithin(e.motion.x, e.motion.y, 100);
			printf("MOUSE MOTION WORKING \n");
		}
		break;
	}
}

void map::whichNodeIsWithin(int const & x, int const & y, int radius)
{
	float minDistance, distance, dx, dy, maxRadius = radius*radius;
	minDistance = 1000000;
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

bool map::mouseOverNode(int const & x, int const & y)
{
	/*
	// what am I pressing?
	Node * whichNode = whichNodeIsWithin(x,y, 100);
	// is that a valid thing to press?
	if(whichNode != NULL)
	{
		// do my action
		selectron = whichNode->ID - 1;
		return true;
	}
	*/
	return false;
}