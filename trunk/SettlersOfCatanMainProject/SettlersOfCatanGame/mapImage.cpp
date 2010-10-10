#include "map.h"

//THIS IS A LIST OF DRAW FUNCTIONS. IT WILL CALL DIFFERENT FUNCTIONS BASED ON THE CURRENT GAME STATE.

//NOTE, WE SHOULD PROBABLY MAKE A UNIVERSAL drawControls(screen) FUNCTION. WE'LL TALK ABOUT THAT LATER.

void map::draw(SDL_Surface * screen, Game * g)
{
	switch(mapState)
	{
		case map::BEGINTURN:
			if (soundQueue == 20)
			{
				g->gameSound->playWAV();
				soundQueue--;
			}
			drawDiceRoll(screen, g);	
			drawPlayerTag(screen, g);
			break;

		case map::MAP:				drawBoard(screen);			drawPlayerTag(screen, g);		drawInstructions(screen, g);break; 
		case map::BUILDCARD:		drawBuildCard(screen);		drawPlayerTag(screen, g);		drawInstructions(screen, g);break;
		case map::RESOURCELIST:		drawResourceList(screen, g);drawPlayerTag(screen, g);		drawInstructions(screen, g); drawVictoryPoints(screen, g);break;
		case map::DEVHAND:			drawDevHand(screen, g);		drawPlayerTag(screen, g);		drawInstructions(screen, g);break;
		case map::TRADE:			drawtradeCard(screen, g);	drawPlayerTag(screen, g);		drawInstructions(screen, g);break;
		case map::BUILDROAD:		drawBoard(screen);			drawPlayerTag(screen, g);drawInstructions(screen, g);
									drawRoadSelectron(screen);		break;
		case map::BUILDSETTLEMENT:	drawBoard(screen);			drawPlayerTag(screen, g);drawInstructions(screen, g);
									drawNodeSelectron(screen);		break;
		case map::BUILDCITY:		drawBoard(screen);			drawPlayerTag(screen, g);drawInstructions(screen, g);
									drawNodeSelectron(screen);		break;
		case map::TURNONESETTLEMENT:		drawBoard(screen);	drawPlayerTag(screen, g);drawInstructions(screen, g);
									drawNodeSelectron(screen);		break;
		case map::TURNONEROAD:		drawBoard(screen);			drawPlayerTag(screen, g);drawInstructions(screen, g);
									drawRoadSelectron(screen);		break;
		case map::TURNTWOSETTLEMENT:		drawBoard(screen);	drawPlayerTag(screen, g);drawInstructions(screen, g);
									drawNodeSelectron(screen);		break;
		case map::TURNTWOROAD:		drawBoard(screen);			drawPlayerTag(screen, g);drawInstructions(screen, g);
									drawRoadSelectron(screen);		break;
		case map::FREETWORESOURCES:	drawResourceGrab(screen);	drawPlayerTag(screen, g);drawInstructions(screen, g);							break;
		case map::FREETWOROADS:		drawBoard(screen); drawRoadSelectron(screen); drawPlayerTag(screen, g);	drawInstructions(screen, g);		break;
		case map::SOMEONEWON:		drawWinScreen(screen);		drawPlayerTag(screen, g);	drawInstructions(screen, g);						break;
		case map::PICKMONOPOLY:		drawResourceGrab(screen); drawPlayerTag(screen, g);	drawInstructions(screen, g);							break;
		case map::SETTHETHIEF:		drawBoard(screen);				drawThiefExplanation(screen, g);drawInstructions(screen, g);
									drawCenterSelectron(screen);	drawPlayerTag(screen, g);		break;
		case map::TRADETARGET:		drawPickTradeTarget(screen, g);	drawPlayerTag(screen, g);	drawInstructions(screen, g);					break;
		case map::TRADEPLAYERSCREEN:		drawtradeCard(screen, g); drawPlayerTag(screen, g);	drawInstructions(screen, g);	break;
		case map::TRADEBANKHARBORSCREEN:	drawtradeCard(screen, g); drawPlayerTag(screen, g);	drawInstructions(screen, g);	break;
	}
	// this is where drawControls(screen) would go, because then it would print on every map screen in addition to the other draw functions.
}

// THESE ARE ALL THE IMAGES LOADED THROUGH map.h AND ITS CPPS

void map::loadImages()
{
	font = TTF_OpenFont( "SNAP.ttf", 72);
	extraTradeRules = load_image( "extraTradeRules.bmp" );
	standardLegend = load_image( "standardLegend.bmp" );
	cancelLegend = load_image( "cancelLegend.bmp" );
	pickToTrade = load_image( "placeholderPickTradeScreen.bmp" );
	thief = load_image( "placeholderThief.bmp ");
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
	extraTradeRules = NULL;
	standardLegend = NULL;
	cancelLegend = NULL;
	pickToTrade = NULL;
	thief = NULL;
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

void map::drawPickTradeTarget(SDL_Surface * screen, Game * g)
{
		apply_surface(	0,
						0,
						pickToTrade,
						screen,
						NULL );
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

void map::drawCenterSelectron(SDL_Surface * screen)
{
	if (centerSelectron >= 0 && centerSelectron <= 143)
	{
		apply_surface(	myCenters[centerSelectron].pixelX,
						myCenters[centerSelectron].pixelY,
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
			apply_surface(	myCenters[i].pixelX, // * (400 / 9) - x - 19,
							myCenters[i].pixelY, // * 50 - 19,
							chitTile[myCenters[i].chitWorth - y],
							screen,
							NULL);
		}
		if(myCenters[i].thiefHere == true)
		{
			apply_surface(	myCenters[i].pixelX, // * (400 / 9) - x - 19,
							myCenters[i].pixelY, // * 50 - 19,
							thief,
							screen,
							NULL);
		}
	}

	//===========================================
	font = TTF_OpenFont( "SNAP.ttf", 20);
	textColor.r = 100;
	textColor.g = 100;
	textColor.b = 200;
	int harborPrintX, harborPrintY;
	for (int i = 0; i < 54; ++i)
	{

		//if	(myNodes[i].pixelY > 440){harborPrintY = myNodes[i].pixelY + 20;}
		//else if (myNodes[i].pixelY <= 200){	harborPrintY = myNodes[i].pixelY - 20;}
		if	(myNodes[i].pixelY > 400)
		{
			harborPrintY = myNodes[i].pixelY + 11;
		}
		else if (myNodes[i].pixelY <= 100)
		{	
			harborPrintY = myNodes[i].pixelY - 11;
		}
		else
		{
			harborPrintY = myNodes[i].pixelY;
		}

		if	(myNodes[i].pixelX > 600)
		{
			harborPrintX = myNodes[i].pixelX + 11;
		}
		else if (myNodes[i].pixelX <= 200)
		{	
			harborPrintX = myNodes[i].pixelX - 11;
		}
		else
		{
			harborPrintX = myNodes[i].pixelX;
		}

		if(myNodes[i].harborType != NULL)
		{
			char buffer [1024];

			char * resAndAmt = "%c";
			char amountResourceStuff;
			switch(myNodes[i].harborType)
			{
			case THREE_TO_ONE: amountResourceStuff = '3'; break;
				case BRICK:	amountResourceStuff = 'B' ; break;
				case WOOD:	amountResourceStuff = 'L' ; break;
				case STONE:	amountResourceStuff = 'S' ; break;
				case SHEEP:	amountResourceStuff = 'E' ; break;
				case WHEAT:	amountResourceStuff = 'W' ; break;
			}
			sprintf(buffer, resAndAmt, amountResourceStuff);
			resourceListMsg[0] = TTF_RenderText_Solid( font, buffer, textColor );
			apply_surface( harborPrintX, harborPrintY, resourceListMsg[0], screen, NULL );
			SDL_FreeSurface(resourceListMsg[0]);
		}
	}
	TTF_CloseFont(font);
	//==========================

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
	font = TTF_OpenFont( "SNAP.ttf", 20);
	textColor.r = 0;
	textColor.g = 255;
	textColor.b = 0;
	char * buffer = "WINNER!";
	resourceListMsg[0] = TTF_RenderText_Solid( font, buffer, textColor );
	apply_surface( 300, 270, resourceListMsg[0], screen, NULL );
	SDL_FreeSurface(resourceListMsg[0]);
	TTF_CloseFont(font);
}

void map::drawVictoryPoints(SDL_Surface * screen, Game * g)
{
	font = TTF_OpenFont( "SNAP.ttf", 20);
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

	char buffer [1024];

	char * resAndAmt = "You Have %d Victory Points!";
	int amountResourceStuff;

	amountResourceStuff = g->p[g->activePlayer].currentVictoryPoints;

	sprintf(buffer, resAndAmt, amountResourceStuff);
	resourceListMsg[0] = TTF_RenderText_Solid( font, buffer, textColor );
	apply_surface( 225, 160, resourceListMsg[0], screen, NULL );
	SDL_FreeSurface(resourceListMsg[0]);
	TTF_CloseFont(font);
}


void map::drawThiefExplanation(SDL_Surface * screen, Game * g)
{
	font = TTF_OpenFont( "SNAP.ttf", 20);
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

	char * buffer = "Place the Thief!";
	resourceListMsg[0] = TTF_RenderText_Solid( font, buffer, textColor );
	apply_surface( 300, 1, resourceListMsg[0], screen, NULL );
	SDL_FreeSurface(resourceListMsg[0]);
	TTF_CloseFont(font);
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
	TTF_CloseFont(font);
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
	TTF_CloseFont(font);
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
	TTF_CloseFont(font);
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
	TTF_CloseFont(font);
}

void map::drawtradeCard(SDL_Surface * screen, Game* g)
{
	apply_surface( 0, 0, tradeCard, screen, NULL );

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
			case 0:	amountResourceStuff = tradebank->temp_brick_give; break;
			case 1:	amountResourceStuff = tradebank->temp_wood_give; break;
			case 2:	amountResourceStuff = tradebank->temp_stone_give; break;
			case 3:	amountResourceStuff = tradebank->temp_sheep_give; break;
			case 4:	amountResourceStuff = tradebank->temp_wheat_give; break;
		}
		sprintf(buffer, resAndAmt, amountResourceStuff);
		resourceListMsg[i] = TTF_RenderText_Solid( font, buffer, textColor );
		apply_surface( 150 + spacingX*i, 337, resourceListMsg[i], screen, NULL );
		SDL_FreeSurface(resourceListMsg[i]);
	}

	for (int i = 0; i < 5; ++i)
	{
		char buffer [1024];

		char * resAndAmt = "%d";
		char * rotResType = specResTypes[i];
		int amountResourceStuff;
		switch(i)
		{
			case 0:	amountResourceStuff = tradebank->temp_brick_recieve; break;
			case 1:	amountResourceStuff = tradebank->temp_wood_recieve; break;
			case 2:	amountResourceStuff = tradebank->temp_stone_recieve; break;
			case 3:	amountResourceStuff = tradebank->temp_sheep_recieve; break;
			case 4:	amountResourceStuff = tradebank->temp_wheat_recieve; break;
		}
		sprintf(buffer, resAndAmt, amountResourceStuff);
		resourceListMsg[i] = TTF_RenderText_Solid( font, buffer, textColor );
		apply_surface( 150 + spacingX*i, 454, resourceListMsg[i], screen, NULL );
		SDL_FreeSurface(resourceListMsg[i]);
	}

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
	for (int i = 0; i < 5; ++i)
	{
		char buffer [1024];

		char * resAndAmt = "%c";
		char amountResourceStuff;
		switch(i)
		{
			case 0:	amountResourceStuff = 'Q'; break;
			case 1:	amountResourceStuff = 'W'; break;
			case 2:	amountResourceStuff = 'E'; break;
			case 3:	amountResourceStuff = 'R'; break;
			case 4:	amountResourceStuff = 'T'; break;
		}
		sprintf(buffer, resAndAmt, amountResourceStuff);
		resourceListMsg[i] = TTF_RenderText_Solid( font, buffer, textColor );
		apply_surface( 150 + spacingX*i, 272, resourceListMsg[i], screen, NULL );
		SDL_FreeSurface(resourceListMsg[i]);
	}

	switch(tradebank->playerNumber)
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
	for (int i = 0; i < 5; ++i)
	{
		char buffer [1024];

		char * resAndAmt = "%c";
		char amountResourceStuff;
		switch(i)
		{
			case 0:	amountResourceStuff = 'A'; break;
			case 1:	amountResourceStuff = 'S'; break;
			case 2:	amountResourceStuff = 'D'; break;
			case 3:	amountResourceStuff = 'F'; break;
			case 4:	amountResourceStuff = 'G'; break;
		}
		sprintf(buffer, resAndAmt, amountResourceStuff);
		resourceListMsg[i] = TTF_RenderText_Solid( font, buffer, textColor );
		apply_surface( 150 + spacingX*i, 511, resourceListMsg[i], screen, NULL );
		SDL_FreeSurface(resourceListMsg[i]);
	}
	TTF_CloseFont(font);

}

void map::drawDiceRoll(SDL_Surface * screen, Game * g)
{
	dice.drawDiceScreen(screen, dice1, dice2);
	font = TTF_OpenFont( "SNAP.ttf", 20);
	textColor.r = 0;
	textColor.g = 255;
	textColor.b = 0;
	char * buffer = "Press Space to Continue!";
	resourceListMsg[0] = TTF_RenderText_Solid( font, buffer, textColor );
	apply_surface( 250, 400, resourceListMsg[0], screen, NULL );
	SDL_FreeSurface(resourceListMsg[0]);
	TTF_CloseFont(font);
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

void map::drawFreeRoadInstructions(SDL_Surface * screen, Game * g)
{
	font = TTF_OpenFont( "SNAP.ttf", 20);
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
	char * buffer = "Place your free road!";
	playerTag = TTF_RenderText_Solid( font, buffer, textColor );
	apply_surface( 277, 1, playerTag, screen, NULL );
	SDL_FreeSurface(playerTag);
	TTF_CloseFont(font);
}

void map::drawFreeSettlementInstructions(SDL_Surface * screen, Game * g)
{
	font = TTF_OpenFont( "SNAP.ttf", 20);
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
	char * buffer = "Place your free settlement!";
	playerTag = TTF_RenderText_Solid( font, buffer, textColor );
	apply_surface( 250, 1, playerTag, screen, NULL );
	SDL_FreeSurface(playerTag);
	TTF_CloseFont(font);
}

void map::drawExtraTradeRules(SDL_Surface * screen, Game * g)
{
	apply_surface(700, 400, extraTradeRules, screen, NULL);
}

void map::drawCancelInstructions(SDL_Surface * screen, Game * g)
{
	apply_surface(700, 0, cancelLegend, screen, NULL);
}

void map::drawStandardInstructions(SDL_Surface * screen, Game * g)
{
	apply_surface(700, 0, standardLegend, screen, NULL);
}

void map::drawInstructions(SDL_Surface * screen, Game * g)
{
	switch(mapState)
	{
		case map::MAP:						drawStandardInstructions(screen, g);break; 
		case map::BUILDCARD:				drawStandardInstructions(screen, g);break;
		case map::RESOURCELIST:				drawStandardInstructions(screen, g);break;
		case map::DEVHAND:					drawStandardInstructions(screen, g);break;
		case map::TRADE:					drawStandardInstructions(screen, g);break;
		case map::BUILDROAD:				drawCancelInstructions(screen, g);	break;
		case map::BUILDSETTLEMENT:			drawCancelInstructions(screen, g);	break;
		case map::BUILDCITY:				drawCancelInstructions(screen, g);	break;
		case map::TURNONESETTLEMENT:		drawFreeSettlementInstructions(screen, g);break;
		case map::TURNONEROAD:				drawFreeRoadInstructions(screen, g);break;
		case map::TURNTWOSETTLEMENT:		drawFreeSettlementInstructions(screen, g);break;
		case map::TURNTWOROAD:				drawFreeRoadInstructions(screen, g);break;
		case map::FREETWORESOURCES:			break;
		case map::FREETWOROADS:				drawFreeRoadInstructions(screen, g);break;
		case map::SOMEONEWON:				break;
		case map::PICKMONOPOLY:				break;
		case map::SETTHETHIEF:				break;
		case map::TRADETARGET:				drawCancelInstructions(screen, g); drawExtraTradeRules(screen, g);	break;
		case map::TRADEPLAYERSCREEN:		drawCancelInstructions(screen, g); drawExtraTradeRules(screen, g);	break;
		case map::TRADEBANKHARBORSCREEN:	drawCancelInstructions(screen, g); drawExtraTradeRules(screen, g);	break;
	}
}


void map::shutdownImages()
{
	SDL_FreeSurface(extraTradeRules);
	SDL_FreeSurface(standardLegend);
	SDL_FreeSurface(cancelLegend);
	SDL_FreeSurface(pickToTrade);
	SDL_FreeSurface(playerTag);
	SDL_FreeSurface(thief);
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

	//THIS FUNCTIONS ARE TRYING TO FREE SURFACES THAT HAVE ALREADY BEEN FREED! THAT MEANS DURING THE CLOSING OF THE APPLICATION IT BREAKS BECAUSE FREEDOM HAS ALREADY BEEN ESTABLISHED!
	//for (int i = 0; i < 5; ++i)
	//{
	//	SDL_FreeSurface(resourceListMsg[i]);
	//}

	//TTF_CloseFont(font);
}
