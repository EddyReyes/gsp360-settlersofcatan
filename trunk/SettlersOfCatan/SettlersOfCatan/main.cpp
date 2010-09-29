#include <iostream>
#include <stdio.h> // printf() 
#include "player.h"
#include "resourceCards.h"
#include "stndrd.h"
#include "graph.h"
#include "sdlManager.h"

using namespace std;

//declarations
static sdlManager& sdlMgr = sdlManager::getInstance();

//screen
SDL_Surface *screen = NULL;
const int WIDTH = 640;
const int HEIGHT = 480;
const int BPP = 32;

void OpeningMenu (int *);
void AssignChitResources(char *);
void DebugOutputResourceChits(char *);
void RollDice(int *, int *);
void tradeWithPlayer(player*, player*, char, char, int, int);

// must be the header for SDL applications 
int main(int argc, char ** argv) 
{
	//intializes everything SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//init fail buster
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout <<"could not initialize SDL" << endl;
		return 1;
	}	
	
	//Initialize SDL_ttf 
	TTF_Init();
	//init fail buster
	if( TTF_Init() != 0 ) 
	{ 
		cout << "could not initialize SDLttf " << endl;
		return 2;
	} 

	//create a new window--->set up screen
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE|SDL_DOUBLEBUF
		/*comment out FULLSCREEN to see console*//*|SDL_FULLSCREEN*/);
	if(!screen)
	{
		cout << "failed to initialize screen" << endl;
		return 2;
	}

	//SDL Load Images
	sdlMgr.loadImages();


	player playerOne, playerTwo, playerThree, playerFour; // declare four players
	rsc ResourceDeck; // declare a resource deck
	int winner = NULL;
	int numOfPlayers;
	int currentTurn;
	char chits[12]; // delcare an array of 12 chits
	srand((unsigned int)time(0));
	OpeningMenu(&numOfPlayers);
	AssignChitResources(chits);
	//DebugOutputResourceChits(chits);


	//initializing players can probably be removed later if the initialization is change
	playerOne.setPlayer('r');
	playerTwo.setPlayer('w');
	playerThree.setPlayer('o');
	playerFour.setPlayer('b');


	// Display the current status of the resource bank
	ResourceDeck.DisplayResourceBankStatus();

	// At this point we give player 2 three of each resource cards (for debugginb purposes)
	playerTwo.drawResource(&ResourceDeck, WOOD, 3);
	playerTwo.drawResource(&ResourceDeck, WHEAT, 3);
	playerTwo.drawResource(&ResourceDeck, STONE, 3);
	playerTwo.drawResource(&ResourceDeck, BRICK, 3);
	playerTwo.drawResource(&ResourceDeck, SHEEP, 3);
	cout << "Player two was given 3 resource cards of each type." << endl << endl;

	// Roll Dice
	int Dice1, Dice2;
	RollDice(&Dice1, &Dice2);
	cout << "Player rolls dice: " << Dice1 << " and " << Dice2 << endl 
		 << "Total: " << Dice1 + Dice2 << endl << endl;

	// Display the current status of the resource bank
	ResourceDeck.DisplayResourceBankStatus();

	// Give the player a resouce according to value rolled and chit value correspondence
	int DiceRollTotal = Dice1+Dice2;
	
	playerOne.drawResource(&ResourceDeck, chits[(DiceRollTotal-1)], 1);
	cout << "Player recieves " << chits[(DiceRollTotal-1)] <<". " << endl;

	// Display the current status of the resource bank
	ResourceDeck.DisplayResourceBankStatus();


	cout << "playerOneStatus:" << endl;
	cout << playerOne.getResource(WHEAT) << endl;
	// Trade cards between player one and player two
	tradeWithPlayer(&playerOne, &playerTwo, WHEAT, STONE, 3, 0);
	//Display playerOne Cards
	cout << "playerOne wheat: " << playerOne.getResource(WHEAT) << endl;
	cout << "playerOne stone: " << playerOne.getResource(STONE) << endl;
	cout << "playerOne brick: " << playerOne.getResource(BRICK) << endl;
	cout << "playerOne sheep: " << playerOne.getResource(SHEEP) << endl;
	cout << "playerOne wood: " << playerOne.getResource(WOOD) << endl;

	//Display playerTwo Cards
	cout << "playerTwo wheat: " << playerTwo.getResource(WHEAT) << endl;	cout << "playerTwo stone: " << playerTwo.getResource(STONE) << endl;	cout << "playerTwo brick: " << playerTwo.getResource(BRICK) << endl;	cout << "playerTwo sheep: " << playerTwo.getResource(SHEEP) << endl;	cout << "playerTwo wood: " << playerTwo.getResource(WOOD) << endl;
	
	
	//shows console graph
	graph();
	system("PAUSE");

SDL_Event e;
	bool running = true;
	// ---- game loop
	do
	{
		sdlMgr.draw(screen);
	
		if(!SDL_PollEvent(&e))
			e.type = SDL_NOEVENT;
		switch(e.type)
		{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_UP:
				sdlMgr.randomRange++;
				if(sdlMgr.randomRange > 6)
					sdlMgr.randomRange = 6;
				break;
			case SDLK_DOWN:
				sdlMgr.randomRange--;
				if(sdlMgr.randomRange < 1)
					sdlMgr.randomRange = 1;
				break;
			case SDLK_LEFT:
				sdlMgr.numDice--;
				if(sdlMgr.numDice < 0)
					sdlMgr.numDice = 1;
				break;
			case SDLK_RIGHT:
				sdlMgr.numDice++;
				if(sdlMgr.numDice > 6)
					sdlMgr.numDice = 5;
				break;
			case SDLK_SPACE:
				sdlMgr.rollDice = true;
				sdlMgr.randomize = true;
				break;
			case SDLK_ESCAPE:
				running = false;
				break;
			}
			break;
		case SDL_QUIT:
			running = false;
			break;
		}
	}
	while(running);

	//release data
	SDL_FreeSurface(screen);
	sdlMgr.shutdown();
	SDL_Quit();

	return 0;
}


//
//        // ensures that memory allocated using SDL_Init is freed 
//        SDL_Quit(); 
//	return 0; 
//}

void OpeningMenu(int *numOfPlayers)
{
	cout << "		Settlers of Catan		"<< endl << endl
		 << "Number of players?: ";
	cin >> *numOfPlayers;
	cout << endl;
}

void AssignChitResources(char *chits)
{
	for(int x = 0; x < 12; x ++)
	{
		int y = rand()%5;
		switch(y)
		{
			case 0: chits[x] = 'L';	break;
			case 1: chits[x] = 'W';  break;
			case 2: chits[x] = 'S';	break;
			case 3: chits[x] = 'B';	break;
			case 4: chits[x] = 'E';	break;
		}
	}
}

void DebugOutputResourceChits(char *chits)
{
	for(int x = 0; x < 12; x ++)
	{
		cout << chits[x] << endl;
	}
}

void RollDice(int *Dice1, int *Dice2)
{
	*Dice1 = rand()%6+1;
	*Dice2 = rand()%6+1;
}

void tradeWithPlayer(player* active_player, player* trade_to_player, char choice_recieve, char choice_give, int num_recieve, int num_give)
{
	if(active_player->getResource(choice_give) >= num_give && trade_to_player->getResource(choice_recieve) >= num_recieve)
	{
		active_player->changeResource(choice_give, -num_give);
		active_player->changeResource(choice_recieve, num_recieve);

		trade_to_player->changeResource(choice_recieve, -num_recieve);
		trade_to_player->changeResource(choice_give, num_give);
	}
}