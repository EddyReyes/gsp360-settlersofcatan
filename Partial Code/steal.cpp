void Steal(player* thief, player* victim)
{
	int totalCards = 0;
	totalCards += victim->getResource(WHEAT);
	totalCards += victim->getResource(WOOD);
	totalCards += victim->getResource(BRICK);
	totalCards += victim->getResource(STONE);
	totalCards += victim->getResource(SHEEP);

	int stolenCard = rand() % totalCards;
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


//this function is supposed to tell people that they need to pick cards to take away
void thiefIsRolled(player p[])
{
	bool tooMany[5] = [];
	for(int i = 1; i < 5; i++)
	{
		int totalCards = 0;
		totalCards += p[i]->getResource(WHEAT);
		totalCards += p[i]->getResource(WOOD);
		totalCards += p[i]->getResource(BRICK);
		totalCards += p[i]->getResource(STONE);
		totalCards += p[i]->getResource(SHEEP);

		if(totalCards > 7)
			tooMany[i] = true;
	}

	totalCards = 0;
	int numCardsToRemove[5] = 0;
	for(int = 1; i < 5; i++)
	{
		if(tooMany[i] == true)
		{
			totalCards += p[i]->getResource(WHEAT);
			totalCards += p[i]->getResource(WOOD);
			totalCards += p[i]->getResource(BRICK);
			totalCards += p[i]->getResource(STONE);
			totalCards += p[i]->getResource(SHEEP);
		}

		if(totalCards % 2 == 1)
			totalCards--;

		totalCards = totalCards / 2;

		numCardsToRemove[i] = totalCards;
	}
}







p[i]

bool endTurn = false;
bool hasRolled = false;
int curPlayer = 1;
//p is the array of players
while(running)//while the game is running, probably have another thing for winner = false
{
	currentPlayer = p[curPlayer];

	while(!hasRolled)
	{
		//play dev card
		//roll
		//after they roll, set hasRolled to true, so it leaves this loop
	}
	while(!endTurn)
	{
		//play dev card
		//build
		//trade
		//end turn
	}
	//probably could take out the if statement below and since it wold keep going through the while loop
	// until they pick end turn
	if(endTurn)//chooses end turn
	{
		currentPlayer = nextPlayer;
		nextPlayer = p[curPlayer];
		curPlayer++;
		if(curPlayer > 4)
			curPlayer = 1;
	}


	//all the stuff in this while(running) loop need to be together