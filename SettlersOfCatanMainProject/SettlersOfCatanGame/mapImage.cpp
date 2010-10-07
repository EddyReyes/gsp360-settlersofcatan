#include "map.h"

//THIS IS A LIST OF DRAW FUNCTIONS. IT WILL CALL DIFFERENT FUNCTIONS BASED ON THE CURRENT GAME STATE.

//NOTE, WE SHOULD PROBABLY MAKE A UNIVERSAL drawControls(screen) FUNCTION. WE'LL TALK ABOUT THAT LATER.

void map::draw(SDL_Surface * screen, Game * g)
{
	switch(mapState)
	{
		case map::BEGINTURN:
bool quit = NULL;
			//While the user hasn't quit 
			while( quit == false ) 
			{ 
			//While there's events to handle 
			while( SDL_PollEvent( &event ) ) 
			{ 
			//If a key was pressed 
		if( event.type == SDL_KEYDOWN ) 
		{ 
			//If 1 was pressed 
			if( event.key.keysym.sym == SDLK_1 ) 
			{ 
			g->gameSound->playWAV();
			drawDiceRoll(screen, g);	
			drawPlayerTag(screen, g);
			}
			break;

		case map::MAP:				drawBoard(screen);			drawPlayerTag(screen, g);		break; 
		case map::BUILDCARD:		drawBuildCard(screen);		drawPlayerTag(screen, g);		break;
		case map::RESOURCELIST:		drawResourceList(screen, g);drawPlayerTag(screen, g);		break;
		case map::DEVHAND:			drawDevHand(screen, g);		drawPlayerTag(screen, g);		break;
		case map::TRADE:			drawtradeCard(screen);		drawPlayerTag(screen, g);		break;
		case map::BUILDROAD:		drawBoard(screen);			drawPlayerTag(screen, g);
									drawRoadSelectron(screen);		break;
		case map::BUILDSETTLEMENT:	drawBoard(screen);			drawPlayerTag(screen, g);
									drawNodeSelectron(screen);		break;
		case map::BUILDCITY:		drawBoard(screen);			drawPlayerTag(screen, g);
									drawNodeSelectron(screen);		break;
		case map::TURNONESETTLEMENT:		drawBoard(screen);	drawPlayerTag(screen, g);
									drawNodeSelectron(screen);		break;
		case map::TURNONEROAD:		drawBoard(screen);			drawPlayerTag(screen, g);
									drawRoadSelectron(screen);		break;
		case map::TURNTWOSETTLEMENT:		drawBoard(screen);	drawPlayerTag(screen, g);
									drawNodeSelectron(screen);		break;
		case map::TURNTWOROAD:		drawBoard(screen);			drawPlayerTag(screen, g);
									drawRoadSelectron(screen);		break;
		case map::FREETWORESOURCES:	drawResourceGrab(screen);	drawPlayerTag(screen, g);	break;
		case map::FREETWOROADS:		drawBoard(screen); drawRoadSelectron(screen); drawPlayerTag(screen, g);  break;
		case map::SOMEONEWON:		drawWinScreen(screen);		drawPlayerTag(screen, g);		break;
	}
	// this is where drawControls(screen) would go, because then it would print on every map screen in addition to the other draw functions.
}

// THESE ARE ALL THE IMAGES LOADED THROUGH map.h AND ITS CPPS

void map::loadImages()
{
	font = TTF_OpenFont( "SNAP.ttf", 72);
	tradeCard = load_image( "tradeCard.bmp" );
	DevHand = load_image( "DevHand.bmp" );
	resourceCard = load_image( "resourceCard.bmp" );
	buildCard = load_image( "buildCard.bmp" );
	roadTile[0] = load_image( "roadRed.bmp" );
	roadTile[1] = load_image( "roadBlue.bmp" );
	roadTile[2] = load_image( "roadWhite.bmp" );
	roadTile[3] = load_image( "roadOrange.bmp" );
	settlementTile[0] = load_image( "settlementRed.bmp" );
	settlementTile[1] = load_image( "settlementBlue.bmp" );
	settlementTile[2] = load_image( "settlementWhite.bmp" );
	settlementTile[3] = load_image( "settlementOrange.bmp" );
	cityTile[0] = load_image( "cityRed.bmp" );
	cityTile[1] = load_image( "cityBlue.bmp" );
	cityTile[2] = load_image( "cityWhite.bmp" );
	cityTile[3] = load_image( "cityOrange.bmp" );
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

void map::initializeImages()
{
	dice.loadImages();
	font = NULL;
	tradeCard = NULL;
	DevHand = NULL;
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
	if (roadSelectron >= 0 && roadSelectron <= 143)
	{
		apply_surface(	myEdges[roadSelectron].pixelX,
						myEdges[roadSelectron].pixelY,
						testSelect,
						screen,
						NULL );
	}
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

	for (int i = 0; i < 54; ++i)
	{
		if (myNodes[i].owner != 4)
		{
			if (myNodes[i].cityType == 1)
			{
				apply_surface(	myNodes[i].pixelX,
								myNodes[i].pixelY,
								settlementTile[myNodes[i].owner],
								screen,
								NULL);
			}
			else if (myNodes[i].cityType == 2)
			{
				apply_surface(	myNodes[i].pixelX,
								myNodes[i].pixelY,
								cityTile[myNodes[i].owner],
								screen,
								NULL);
			}
		}
	}
	for (int i = 0; i < 144; ++i)
	{
		if (myEdges[i].owner != 4)
		{
			apply_surface(	myEdges[i].pixelX,
							myEdges[i].pixelY,
							roadTile[myEdges[i].owner],
							screen,
							NULL);
		}
	}
}

//more draws!
////////////////////////////////////////////

void map::drawWinScreen(SDL_Surface * screen)
{

}

void map::drawBuildCard(SDL_Surface * screen)
{
	apply_surface( 0, 0, buildCard, screen, NULL );
}

void map::drawResourceList(SDL_Surface * screen, Game * g)
{
	apply_surface( 0, 0, resourceCard, screen, NULL );

	char * specResTypes[5] = {"Brick", "Wood", "Stone", "Sheep", "Wheat"};
	int spacingX = 103;

	font = TTF_OpenFont( "SNAP.ttf", 72);
	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 0;

	for (int i = 0; i < 5; ++i)
	{
		char buffer [1024];

		char * resAndAmt = "%d";
		char * rotResType = specResTypes[i];
		int amountResourceStuff;
		switch(i)
		{
			case 0:	amountResourceStuff = g->p[g->activePlayer].brick; break;
			case 1:	amountResourceStuff = g->p[g->activePlayer].wood; break;
			case 2:	amountResourceStuff = g->p[g->activePlayer].stone; break;
			case 3:	amountResourceStuff = g->p[g->activePlayer].sheep; break;
			case 4:	amountResourceStuff = g->p[g->activePlayer].wheat; break;
		}
		sprintf(buffer, resAndAmt, amountResourceStuff);
		resourceListMsg[i] = TTF_RenderText_Solid( font, buffer, textColor );
		apply_surface( 160 + spacingX*i, 420, resourceListMsg[i], screen, NULL );
		SDL_FreeSurface(resourceListMsg[i]);
	}
}

void map::drawResourceGrab(SDL_Surface * screen)
{
	apply_surface( 0, 0, resourceCard, screen, NULL );

	char * specResTypes[5] = {"Brick", "Wood", "Stone", "Sheep", "Wheat"};
	int spacingX = 103;

	font = TTF_OpenFont( "SNAP.ttf", 72);
	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 0;

	for (int i = 0; i < 5; ++i)
	{
		char buffer [1024];

		char * resAndAmt = "%c";
		char amountResourceStuff;
		switch(i)
		{
			case 0:	amountResourceStuff = 'B' ; break;
			case 1:	amountResourceStuff = 'L' ; break;
			case 2:	amountResourceStuff = 'S' ; break;
			case 3:	amountResourceStuff = 'E' ; break;
			case 4:	amountResourceStuff = 'W' ; break;
		}
		sprintf(buffer, resAndAmt, amountResourceStuff);
		resourceListMsg[i] = TTF_RenderText_Solid( font, buffer, textColor );
		apply_surface( 160 + spacingX*i, 420, resourceListMsg[i], screen, NULL );
		SDL_FreeSurface(resourceListMsg[i]);
	}
}

void map::drawPlayerTag(SDL_Surface * screen, Game * g)
{
	char buffer [1024];
	font = TTF_OpenFont( "SNAP.ttf", 40);
	switch(g->activePlayer)
	{
	case 0: 
		textColor.r = 255;
		textColor.g = 0;
		textColor.b = 0;
		break;
	case 1:
		textColor.r = 0;
		textColor.g = 0;
		textColor.b = 255;
		break;
	case 2:
		textColor.r = 255;
		textColor.g = 255;
		textColor.b = 255;
		break;
	case 3:
		textColor.r = 255;
		textColor.g = 133;
		textColor.b = 0;
		break;
	}
	int playerNumber = g->activePlayer + 1;
	char * playerTurnCharStar = "Player %d";
	sprintf(buffer, playerTurnCharStar, playerNumber);
	playerTag = TTF_RenderText_Solid( font, buffer, textColor );
	apply_surface( 30, 20, playerTag, screen, NULL );
	SDL_FreeSurface(playerTag);
}

void map::drawDevHand(SDL_Surface * screen, Game * g)
{
	apply_surface( 0, 0, DevHand, screen, NULL );
	char * specResTypes[5] = {"Brick", "Wood", "Stone", "Sheep", "Wheat"};
	int spacingX = 105;

	font = TTF_OpenFont( "SNAP.ttf", 72);
	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 0;

	for (int i = 0; i < 5; ++i)
	{
		char buffer [1024];

		char * resAndAmt = "%d";
		char * rotResType = specResTypes[i];
		int amountResourceStuff;
		switch(i)
		{
			case 0:	amountResourceStuff = g->p[g->activePlayer].inHandTwoRoads; break;
			case 1:	amountResourceStuff = g->p[g->activePlayer].inHandYearOfPlenty; break;
			case 2:	amountResourceStuff = g->p[g->activePlayer].inHandMonopolies; break;
			case 3:	amountResourceStuff = g->p[g->activePlayer].inHandSoldiers; break;
			case 4:	amountResourceStuff = g->p[g->activePlayer].inHandVictoryPoints; break;
		}
		sprintf(buffer, resAndAmt, amountResourceStuff);
		resourceListMsg[i] = TTF_RenderText_Solid( font, buffer, textColor );
		apply_surface( 150 + spacingX*i, 300, resourceListMsg[i], screen, NULL );
		SDL_FreeSurface(resourceListMsg[i]);
	}

	for (int i = 0; i < 5; ++i)
	{
		char buffer [1024];

		char * resAndAmt = "%c";
		char amountResourceStuff;
		switch(i)
		{
			case 0:	amountResourceStuff = 'R'; break;
			case 1:	amountResourceStuff = 'Y'; break;
			case 2:	amountResourceStuff = 'M'; break;
			case 3:	amountResourceStuff = 'S'; break;
			case 4:	amountResourceStuff = 'V'; break;
		}
		sprintf(buffer, resAndAmt, amountResourceStuff);
		resourceListMsg[i] = TTF_RenderText_Solid( font, buffer, textColor );
		apply_surface( 150 + spacingX*i, 360, resourceListMsg[i], screen, NULL );
		SDL_FreeSurface(resourceListMsg[i]);
	}
}

void map::drawtradeCard(SDL_Surface * screen)
{
	apply_surface( 0, 0, tradeCard, screen, NULL );
}

void map::drawDiceRoll(SDL_Surface * screen, Game * g)
{
	dice.drawDiceScreen(screen, dice1, dice2);
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


void map::shutdownImages()
{
	SDL_FreeSurface(playerTag);
	SDL_FreeSurface(tradeCard);
	SDL_FreeSurface(DevHand);
	SDL_FreeSurface(buildCard);
	SDL_FreeSurface(resourceCard);
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
	for (int i = 0; i < 4; ++i)
	{
		SDL_FreeSurface(settlementTile[i]);
		SDL_FreeSurface(cityTile[i]);
		SDL_FreeSurface(roadTile[i]);
	}
	for (int i = 0; i < 5; ++i)
	{
		SDL_FreeSurface(resourceListMsg[i]);
	}
	TTF_CloseFont(font);
}