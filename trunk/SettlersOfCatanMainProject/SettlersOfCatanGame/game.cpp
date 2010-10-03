#include "game.h"
#include "map.h"
#include "sdl/sdl.h"
#include "menu.h"
#include <ctime>

Game::Game()
{
	//die = new Dice[2];
	gameState = Game::MENU;
	underlyingBoard.initializeCenters();
	underlyingBoard.loadImages();
	m.loadImages();
	changeTime = 5000;
	timer = 0;
	placeHolderTurnTwo = 0;
	srand(time(0));
	rand();
	ownerLargestArmy = NULL;
	ownerLongestRoad = NULL;
}

void Game::initGame(int const & a_numPlayers)
{
	numPlayers = a_numPlayers;
	p = new player[numPlayers];
	activePlayer = 0;
	for (int i = 0; i < numPlayers; ++i)
	{
		p[i].ID = i;
	}
}

void Game::shutdown(void)
{
	underlyingBoard.shutdownImages();
	m.shutdownImages();
}

void Game::draw(SDL_Surface * screen)
{
	switch(gameState)
	{
	case Game::MENU:

		SDL_FillRect(screen, 0, 0);
		m.draw(screen);
		SDL_Flip(screen);

		break;

	case Game::GAME:
		//printf("We are INSIDE the game!!!\n");

		SDL_FillRect(screen, 0, 0);
		underlyingBoard.draw(screen, &p[activePlayer]);
		SDL_Flip(screen);

		break;
	}

}
void Game::update(int ms)
{
	timer += ms;

	if(timer >= changeTime)
	{
		timer -= changeTime;
	}
	switch(gameState)
	{
	case Game::MENU:
		break;
	case Game::GAME:
		if(underlyingBoard.mapState == map::ENDTURN)
		{
			if (underlyingBoard.overallTurn == 2)
			{
				placeHolderTurnTwo++;
				activePlayer = 0;
			}
			cout << "placeHolderTurnTwo is " << placeHolderTurnTwo << endl;
			//cout << "placeHolderTurnTwo is " << placeHolderTurnTwo << endl;
			activePlayer++;
			if (activePlayer >= numPlayers)
			{
				activePlayer = 0;
				underlyingBoard.overallTurn++;
			}
			cout << "placeHolderTurnTwo is " << placeHolderTurnTwo << endl;
			cout << "Overall turn is " << underlyingBoard.overallTurn << endl;
			//cout << "placeHolderTurnTwo is " << placeHolderTurnTwo << endl;
			//cout << "Overall turn is " << underlyingBoard.overallTurn << endl;

			if (underlyingBoard.overallTurn == 2)
			{
				if (placeHolderTurnTwo > (numPlayers - 1))
				{
					underlyingBoard.overallTurn++;
					underlyingBoard.mapState = map::MAP;
				}
				else
				{
					activePlayer = (numPlayers - 1) - placeHolderTurnTwo;
					underlyingBoard.mapState = map::TURNTWOSETTLEMENT;
				}
			}
			else if (underlyingBoard.overallTurn == 1)
			{
				underlyingBoard.mapState = map::TURNONESETTLEMENT;
			}

			if (underlyingBoard.overallTurn >= 3)
			{
				underlyingBoard.dice1 = rand() % 6 + 1;
				underlyingBoard.dice2 = rand() % 6 + 1;
				cout << "A WHOLE NEW WORLD! TURN " << underlyingBoard.overallTurn << endl;
				underlyingBoard.mapState = map::BEGINTURN;
				cout << "A WHOLE NEW WORLD! TURN " << underlyingBoard.overallTurn << endl;
			}
		}


		break;
	}
}

void Game::menuInput(SDL_Event & e)
{
	////////
	////this will be moving into menu
	switch(e.type)
	{
	case SDL_KEYDOWN:
		int num = 0;
		switch(e.key.keysym.sym)
		{
		case SDLK_3:	num = 3;	break;
		case SDLK_4:	num = 4;	break;
		}
		if(num >= 3)
		{
			initGame(num);
			gameState = Game::GAME;
		}
		break;
	}/////////////////////////////////
}
//Mouse controls/mouse down condition
bool mouse_down = false;

//if on Game object(s) condition
bool on_object = false;

void Game::gameInput(SDL_Event & e)
{
	underlyingBoard.handleInput(e, &p[activePlayer]);
}
void Game::input(SDL_Event & e)
{
	switch(gameState)
	{
	case Game::MENU:
		menuInput(e);
		break;
	case Game::GAME:
		gameInput(e);
		break;
	}
}

int Game::calculateVictoryPoints(player* p)
{
	int tempVP = 0;

	tempVP += 5 - p->getNumUnusedSettlements();//settlements
	tempVP += (4 - p->getNumUnusedCities()) * 2;//cities

	tempVP += p->getNumUsedVictoryPoints();//played victory points

	if(p->getHasLargestArmy())
		tempVP += 2;//largest army

	if(p->getHasLongestRoad())
		tempVP += 2;//longest road

	p->setVictoryPoints(tempVP);//sets the player's victory points

	return tempVP;
}

void Game::calcLargestArmy(player* p)
{
	if(p->getNumUsedSoldiers() >= 3)
	{
		if(ownerLargestArmy == NULL)
		{
			p->awardLargestArmy();//the player is the first to get to 3
			ownerLargestArmy = p;
		}
		else if(p->getNumUsedSoldiers() > ownerLargestArmy->getNumUsedSoldiers())
		{
			p->awardLargestArmy();
			ownerLargestArmy->retractLargestArmy();
		}
	}
}

void Game::steal(player* thief, player* victim)
{
	int totalCards = 0;
	totalCards += victim->getResource(WHEAT);
	totalCards += victim->getResource(WOOD);
	totalCards += victim->getResource(BRICK);
	totalCards += victim->getResource(STONE);
	totalCards += victim->getResource(SHEEP);

	int stolenCard = rand() % totalCards + 1;
	char stolenType = ' ';

	if(stolenCard < victim->getResource(WHEAT))
		stolenType = WHEAT;
	else if(stolenCard < victim->getResource(WHEAT) + victim->getResource(WOOD))
		stolenType = WOOD;
	else if(stolenCard < victim->getResource(WHEAT) + victim->getResource(WOOD) + victim->getResource(BRICK))
		stolenType = BRICK;
	else if(stolenCard < victim->getResource(WHEAT) + victim->getResource(WOOD) + victim->getResource(BRICK) + victim->getResource(STONE))
		stolenType = STONE;
	else
		stolenType = SHEEP;

	thief->changeResource(stolenType, 1);
	victim->changeResource(stolenType, -1);
}

void Game::thiefIsRolled(rsc* resDeck, player* p[])//, int numPlayers)//since this is in the game class, it shouldnt need to be passed
{
	int* numCardsToRemove;
	numCardsToRemove = new int[numPlayers];

	for(int i = 0; i < numPlayers; i++)
	{
		int totalCards = 0;
		totalCards += p[i]->getResource(WHEAT);
		totalCards += p[i]->getResource(WOOD);
		totalCards += p[i]->getResource(BRICK);
		totalCards += p[i]->getResource(STONE);
		totalCards += p[i]->getResource(SHEEP);

		if(totalCards > 7)
		{
			if(totalCards % 2 == 1)
			{
				totalCards--;
				numCardsToRemove[i] = totalCards / 2;
				totalCards++;
			}
			else
				numCardsToRemove[i] = totalCards / 2;

			while(numCardsToRemove[i] != 0)
			{
				char stolenType = ' ';
				int randCard = (rand() % totalCards) + 1;

				if(randCard < p[i]->getResource(WHEAT))
					stolenType = WHEAT;
				else if(randCard < p[i]->getResource(WHEAT) + p[i]->getResource(WOOD))
					stolenType = WOOD;
				else if(randCard < p[i]->getResource(WHEAT) + p[i]->getResource(WOOD) + p[i]->getResource(BRICK))
					stolenType = BRICK;
				else if(randCard < p[i]->getResource(WHEAT) + p[i]->getResource(WOOD) + p[i]->getResource(BRICK) + p[i]->getResource(STONE))
					stolenType = STONE;
				else
					stolenType = SHEEP;

				resDeck->returnToResourcePool(stolenType, 1);
				p[i]->changeResource(stolenType, -1);
				numCardsToRemove[i]--;
				totalCards--;
			}//end of while(numCardsToRemove[i] != 0)
		}//end of if(totalCards > 7)
	}//end of for(int i = 0; i < numPlayers; i++)

	delete [] numCardsToRemove;
}
