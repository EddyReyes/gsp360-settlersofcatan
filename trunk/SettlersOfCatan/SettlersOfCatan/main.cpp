#include <iostream>
#include "player.h"
#include "resourceCards.h"
#include "stndrd.h"

using namespace std;

void OpeningMenu (int *);
void AssignChitResources(char *);
void DebugOutputResourceChits(char *);
void RollDice(int *, int *);

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

	cout << "Player recieves " << chits[DiceRollTotal-1] <<". " << endl;
	playerOne.drawResource(&ResourceDeck, chits[DiceRollTotal-1], 1);

	// Display the current status of the resource bank
	ResourceDeck.DisplayResourceBankStatus();

	////openingLayout();
	////comeoutTurn();
	//while (winner == NULL)
	//{
	//	//doNextTurn();
	//}
}

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