#include "tradebank.h"
#include "game.h"

TradeBank::TradeBank()
{
	wood_give = 0;
	wheat_give = 0;
	stone_give = 0;
	sheep_give = 0;
	brick_give = 0;

	wood_recieve = 0;
	wheat_recieve = 0;
	stone_recieve = 0;
	sheep_recieve = 0;
	brick_recieve = 0;

	active_set = false;
	trader_set = false;

	temp_wood_give = 0;
	temp_wheat_give = 0;
	temp_stone_give = 0;
	temp_sheep_give = 0;
	temp_brick_give = 0;
	
	temp_wood_recieve = 0;
	temp_wheat_recieve = 0;
	temp_stone_recieve = 0;
	temp_sheep_recieve = 0;
	temp_brick_recieve = 0;

	playerNumber = 0;
}

bool TradeBank::setGiveResources(Game* g)
{
	if(g->activePlayer != playerNumber)
	{
		if(g->p[g->activePlayer].getResource(WOOD) >= temp_wood_give)
			wood_give = temp_wood_give;
		else
			return false;
		
		if(g->p[g->activePlayer].getResource(WHEAT) >= temp_wheat_give)
			wheat_give = temp_wheat_give;
		else
			return false;
		
		if(g->p[g->activePlayer].getResource(STONE) >= temp_stone_give)
			stone_give = temp_stone_give;
		else
			return false;

		if(g->p[g->activePlayer].getResource(SHEEP) >= temp_sheep_give)
			sheep_give = temp_sheep_give;
		else
			return false;

		if(g->p[g->activePlayer].getResource(BRICK) >= temp_brick_give)
			brick_give = temp_brick_give;
		else
			return false;
			
		active_set = true;
		return true;
	}
	return false;
}

bool TradeBank::setRecieveResources(Game* g)
{
	if(g->activePlayer != playerNumber)
	{
		if(g->p[playerNumber].getResource(WOOD) >= temp_wood_recieve)
			wood_recieve = temp_wood_recieve;
		else
			return false;
	
		if(g->p[playerNumber].getResource(WHEAT) >= temp_wheat_recieve)
			wheat_recieve = temp_wheat_recieve;
		else
			return false;
		
		if(g->p[playerNumber].getResource(STONE) >= temp_stone_recieve)
			stone_recieve = temp_stone_recieve;
		else
			return false;

		if(g->p[playerNumber].getResource(SHEEP) >= temp_sheep_recieve)
			sheep_recieve = temp_sheep_recieve;
		else
			return false;

		if(g->p[playerNumber].getResource(BRICK) >= temp_brick_recieve)
			brick_recieve = temp_brick_recieve;
		else
			return false;
		trader_set = true;
		return true;
	}
	return false;
}

bool TradeBank::trade(Game* g)
{
	if(active_set && trader_set && g->activePlayer != playerNumber)
	{
		//taking away the resources that the g->p[g->activePlayer]   (active)   player is trading
		g->p[g->activePlayer].changeResource(WOOD, -wood_give);
		g->p[g->activePlayer].changeResource(WHEAT, -wheat_give);
		g->p[g->activePlayer].changeResource(STONE, -stone_give);
		g->p[g->activePlayer].changeResource(SHEEP, -sheep_give);
		g->p[g->activePlayer].changeResource(BRICK, -brick_give);

		//adding the resources that the g->p[g->activePlayer]    (active)    player wants
		g->p[g->activePlayer].changeResource(WOOD, wood_recieve);
		g->p[g->activePlayer].changeResource(WHEAT, wheat_recieve);
		g->p[g->activePlayer].changeResource(STONE, stone_recieve);
		g->p[g->activePlayer].changeResource(SHEEP, sheep_recieve);
		g->p[g->activePlayer].changeResource(BRICK, brick_recieve);

		//adding the resources to the g->p[playerNumber] (trader)that the active player gave
		g->p[playerNumber].changeResource(WOOD, wood_give);
		g->p[playerNumber].changeResource(WHEAT, wheat_give);
		g->p[playerNumber].changeResource(STONE, stone_give);
		g->p[playerNumber].changeResource(SHEEP, sheep_give);
		g->p[playerNumber].changeResource(BRICK, brick_give);

		//taking away the resources that the g->p[playerNumber](trader) is giving to the active player
		g->p[playerNumber].changeResource(WOOD, -wood_recieve);
		g->p[playerNumber].changeResource(WHEAT, -wheat_recieve);
		g->p[playerNumber].changeResource(STONE, -stone_recieve);
		g->p[playerNumber].changeResource(SHEEP, -sheep_recieve);
		g->p[playerNumber].changeResource(BRICK, -brick_recieve);

		ResetBank();

		return true;
	}
	return false;
}

void TradeBank::ResetBank()
{
	//resetting everything so its ready for the next trade
	wood_give = 0;
	wheat_give = 0;
	stone_give = 0;
	sheep_give = 0;
	brick_give = 0;

	wood_recieve = 0;
	wheat_recieve = 0;
	stone_recieve = 0;
	sheep_recieve = 0;
	brick_recieve = 0;

	temp_wood_give = 0;
	temp_wheat_give = 0;
	temp_stone_give = 0;
	temp_sheep_give = 0;
	temp_brick_give = 0;

	temp_wood_recieve = 0;
	temp_wheat_recieve = 0;
	temp_stone_recieve = 0;
	temp_sheep_recieve = 0;
	temp_brick_recieve = 0;

	active_set = false;
	trader_set = false;

	cout << "Trade Bank Reset!" << endl;
}

bool TradeBank::setGiveResources(Game* g, int a_trader_num, int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick)
{
	cout << "Just entered setGiveResources!" << endl;
	if(g->activePlayer != a_trader_num)
	{
		cout << "Inside if statement" << endl;
		cout << "num wood player owned" << g->p[g->activePlayer].getResource(WOOD) << endl;
		cout << "num passed for wood" << a_wood << endl;
		if(g->p[g->activePlayer].getResource(WOOD) >= a_wood)
			this->wood_give = a_wood;
		else
			return false;

		cout << "woodactive is set" << endl;

		if(g->p[g->activePlayer].getResource(WHEAT) >= a_wheat)
			wheat_give = a_wheat;
		else
			return false;

		cout << "wheatactive is set" << endl;

		if(g->p[g->activePlayer].getResource(STONE) >= a_stone)
			stone_give = a_stone;
		else
			return false;
		
		cout << "stoneactive is set" << endl;

		if(g->p[g->activePlayer].getResource(SHEEP) >= a_sheep)
			sheep_give = a_sheep;
		else
			return false;
		
		cout << "sheepactive is set" << endl;

		if(g->p[g->activePlayer].getResource(BRICK) >= a_brick)
			brick_give = a_brick;
		else
			return false;

		cout << "brickactive is set" << endl;

		active_set = true;
		cout << "active_set = true!" << endl;
		return true;
	}
	return false;
}

bool TradeBank::setRecieveResources(Game* g, int a_trader_num, int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick)
{
	if(g->activePlayer != a_trader_num)
	{
		if(g->p[a_trader_num].getResource(WOOD) >= a_wood)
			wood_recieve = a_wood;
		else
			return false;
		
		if(g->p[a_trader_num].getResource(WHEAT) >= a_wheat)
			wheat_recieve = a_wheat;
		else
			return false;

		if(g->p[a_trader_num].getResource(STONE) >= a_stone)
			stone_recieve = a_stone;
		else
			return false;
		
		if(g->p[a_trader_num].getResource(SHEEP) >= a_sheep)
			sheep_recieve = a_sheep;
		else
			return false;
		
		if(g->p[a_trader_num].getResource(BRICK) >= a_brick)
			brick_recieve = a_brick;
		else
			return false;

		trader_set = true;
		return true;
	}
	return false;
}

bool TradeBank::trade(Game* g, int a_trader_num)
{
	if(active_set == true && trader_set == true && g->activePlayer != a_trader_num)//so it wont try to trade to null players
	{
		//taking away the resources that the g->p[g->activePlayer]   (active)   player is trading
		g->p[g->activePlayer].changeResource(WOOD, -wood_give);
		g->p[g->activePlayer].changeResource(WHEAT, -wheat_give);
		g->p[g->activePlayer].changeResource(STONE, -stone_give);
		g->p[g->activePlayer].changeResource(SHEEP, -sheep_give);
		g->p[g->activePlayer].changeResource(BRICK, -brick_give);

		//adding the resources that the g->p[g->activePlayer]    (active)    player wants
		g->p[g->activePlayer].changeResource(WOOD, wood_recieve);
		g->p[g->activePlayer].changeResource(WHEAT, wheat_recieve);
		g->p[g->activePlayer].changeResource(STONE, stone_recieve);
		g->p[g->activePlayer].changeResource(SHEEP, sheep_recieve);
		g->p[g->activePlayer].changeResource(BRICK, brick_recieve);

		//adding the resources to the g->p[a_trader_num] (trader)that the active player gave
		g->p[a_trader_num].changeResource(WOOD, wood_give);
		g->p[a_trader_num].changeResource(WHEAT, wheat_give);
		g->p[a_trader_num].changeResource(STONE, stone_give);
		g->p[a_trader_num].changeResource(SHEEP, sheep_give);
		g->p[a_trader_num].changeResource(BRICK, brick_give);

		//taking away the resources that the g->p[a_trader_num](trader) is giving to the active player
		g->p[a_trader_num].changeResource(WOOD, -wood_recieve);
		g->p[a_trader_num].changeResource(WHEAT, -wheat_recieve);
		g->p[a_trader_num].changeResource(STONE, -stone_recieve);
		g->p[a_trader_num].changeResource(SHEEP, -sheep_recieve);
		g->p[a_trader_num].changeResource(BRICK, -brick_recieve);

		//resetting everything so its ready for the next trade
		wood_give = 0;
		wheat_give = 0;
		stone_give = 0;
		sheep_give = 0;
		brick_give = 0;

		wood_recieve = 0;
		wheat_recieve = 0;
		stone_recieve = 0;
		sheep_recieve = 0;
		brick_recieve = 0;
	
		active_set = false;
		trader_set = false;
		return true;
	}
	return false;
}

bool TradeBank::tradeWithBank(char harbor_type, Game* g, char choice_recieve, char choice_give, int num_recieve)
{
	switch(harbor_type)
	{
	case WOOD:
		if(g->p[g->activePlayer].getResource(WOOD) >= 2 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(WOOD, -2 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(WOOD, 2 * num_recieve);
			return true;
		}
		break;
	case WHEAT:
		if(g->p[g->activePlayer].getResource(WHEAT) >= 2 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(WHEAT, -2 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(WHEAT, 2 * num_recieve);
			return true;
		}
		break;
	case STONE:
		if(g->p[g->activePlayer].getResource(STONE) >= 2 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(STONE, -2 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(STONE, 2 * num_recieve);
			return true;
		}
		break;
	case BRICK:
		if(g->p[g->activePlayer].getResource(BRICK) >= 2 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(BRICK, -2 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(BRICK, 2 * num_recieve);
			return true;
		}
		break;
	case SHEEP:
		if(g->p[g->activePlayer].getResource(SHEEP) >= 2 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(SHEEP, -2 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(SHEEP, 2 * num_recieve);
			return true;
		}
		break;
	case THREE_TO_ONE:
		if(g->p[g->activePlayer].getResource(choice_give) >= 3 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(choice_give, -3 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(choice_give, 3 * num_recieve);
			return true;
		}
	default:
		if(g->p[g->activePlayer].getResource(choice_give) >= 4 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(choice_give, -4 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(choice_give, 4 * num_recieve);
			return true;
		}
	};
	return false;
}

bool TradeBank::tradeWithBank(Game* g, char choice_recieve, char choice_give, int num_recieve)
{
	if(g->p[g->activePlayer].getResource(choice_give) >= 4 * num_recieve)
	{
		g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
		g->p[g->activePlayer].changeResource(choice_give, -4 * num_recieve);
		g->underlyingBoard->rsc.returnToResourcePool(choice_give, 4 * num_recieve);
		return true;
	}
	return false;
}