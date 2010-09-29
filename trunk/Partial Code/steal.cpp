void Steal(player* thief, player* victim)
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


//this function is supposed to tell people that they need to pick cards to take away
void thiefIsRolled(player p[])
{
	bool tooMany[5] = 0;
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
	int numCardsToRemove[5] = 0;//this is holding the number of cards to remove for each player
	for(int = 1; i < 5; i++)
	{
		totalCards = 0;
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

	for(int i = 1; i < 5; i++)
	{
		if(numCardsToRemove[i] != 0)
		{

			totalCards = 0;
			totalCards += p[i]->getResource(WHEAT);
			totalCards += p[i]->getResource(WOOD);
			totalCards += p[i]->getResource(BRICK);
			totalCards += p[i]->getResource(STONE);
			totalCards += p[i]->getResource(SHEEP);


			int* randCard;
			randCard = new int [numCardsToRemove[i]];
			for(int j = 0; j < numCardsToRemove[i]; j++)
			{
				randCard[j] = (rand() % totalCards) + 1;

				for(int k = 0; k < numCardsToRemove[i]; k++)
				{
					if(k != j)//this is so it doesnt check the same number
					{
						//this is supposed to make sure the numbers arent the same and assign a new number
						if(randCard[j] == randCard[k])
						{
							while(randCard[j] == randCard[k])//this should make sure it doesnt put the same number back in
								randCard[j] = (rand() % totalCards) + 1;
						}
					}
				}
			}

			for(int d = 0; d < numCardsToRemove[i]; d++)
			{
				char stolenType = ' ';

				if(randCard[d] < p[i]->getResource(WHEAT))
					stolenType = WHEAT;
				else if(randCard[d] < p[i]->getResource(WHEAT) + p[i]->getResource(WOOD))
					stolenType = WOOD;
				else if(randCard[d] < p[i]->getResource(WHEAT) + p[i]->getResource(WOOD) + p[i]->getResource(BRICK))
					stolenType = BRICK;
				else if(randCard[d] < p[i]->getResource(WHEAT) + p[i]->getResource(WOOD) + p[i]->getResource(BRICK) + p[i]->getResource(STONE))
					stolenType = STONE;
				else
					stolenType = SHEEP;

				p[i]->changeResource(stolenType, -1);
			}

		}//end of if(numCardsToRemove[i] != 0)
	}//end of if for actually removing cards
}


//need these variables for turns
bool endTurn = false;//if they pick end turn, it will leave the while loop
bool hasRolled = false;//bool for if the dice have been rolled yet
int curPlayer = 1;//player number, to compare later on, to reset it back to one, should be a variable
int numPlayers = 4;//this variable is the one needed for ^ but it might already be in the hting
//p is the array of players

while(running)//while the game is running, probably have another thing for winner = false
{
	while(!hasRolled)
	{
		//play dev card
		//p[curPlayer].playdevCard//not exactly sure how this will work
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
		curPlayer++;
		endTurn = false;//need to reset back to false, so for the next player, it goes in the right loop
		hasRolled = false;
		if(curPlayer > numPlayers)//this may need to be changed for the actual game
			curPlayer = 1;
	}
}
//all the stuff in this while(running) loop need to be together