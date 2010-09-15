#include <iostream>
#include "player.h"
#include "resourceCards.h"
#include "stndrd.h"

using namespace std;

void OpeningMenu (int *);
void AssignChitResources(char *);
void DebugOutputResourceChits(char *);


void main()
{
	player playerOne, playerTwo, playerThree, playerFour; // declare four players
	rsc ResourceDeck; // declare a resource deck
	int winner = NULL;
	int numOfPlayers;
	int currentTurn;
	char chits[12]; // delcare an array of 12 chits
	srand((unsigned int)time(0));
	OpeningMenu(&numOfPlayers);
	AssignChitResources(&chits[12]);
	//DebugOutputResourceChits(&chits[12]);

	// At this point we give player 2 three of each resource cards (for debugginb purposes)
	playerTwo.drawResource(&ResourceDeck, WOOD, 3);
	playerTwo.drawResource(&ResourceDeck, WHEAT, 3);
	playerTwo.drawResource(&ResourceDeck, STONE, 3);
	playerTwo.drawResource(&ResourceDeck, BRICK, 3);
	playerTwo.drawResource(&ResourceDeck, SHEEP, 3);

	//openingLayout();
	//comeoutTurn();
	while (winner == NULL)
	{
		//doNextTurn();
	}
}

void OpeningMenu(int *numOfPlayers)
{
	cout << "		Settlers of Catan		"<< endl << endl
		 << "Number of players?: ";
	cin >> *numOfPlayers;
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