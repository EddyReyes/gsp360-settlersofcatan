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

	//active = NULL;
	//trader = NULL;

	active_set = false;
	trader_set = false;
}

bool TradeBank::setGiveResources(Game* g, int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick)
{
	active = g->p[g->activePlayer];

	if(active.getResource(WOOD) < a_wood)
		return false;
	wood_give = a_wood;

	if(active.getResource(WHEAT) < a_wheat)
		return false;
	wheat_give = a_wheat;

	if(active.getResource(STONE) < a_stone)
		return false;
	stone_give = a_stone;

	if(active.getResource(SHEEP) < a_sheep)
		return false;
	sheep_give = a_sheep;

	if(active.getResource(BRICK) < a_brick)
		return false;
	brick_give = a_brick;

	active_set = true;
	return true;
}

bool TradeBank::setRecieveResources(Game* g, int a_trader_num, int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick)
{
	trader = g->p[a_trader_num];

	if(trader.getResource(WOOD) < a_wood)
		return false;
	wood_recieve = a_wood;

	if(trader.getResource(WHEAT) < a_wheat)
		return false;
	wheat_recieve = a_wheat;

	if(trader.getResource(STONE) < a_stone)
		return false;
	stone_recieve = a_stone;

	if(trader.getResource(SHEEP) < a_sheep)
		return false;
	sheep_recieve = a_sheep;

	if(trader.getResource(BRICK) < a_brick)
		return false;
	brick_recieve = a_brick;

	trader_set = true;
	return true;
}

bool TradeBank::trade()
{
	if(active_set == true && trader_set == true)//so it wont try to trade to null players
	{
		//taking away the resources that the active player is trading
		active.changeResource(WOOD, -wood_give);
		active.changeResource(WHEAT, -wheat_give);
		active.changeResource(STONE, -stone_give);
		active.changeResource(SHEEP, -sheep_give);
		active.changeResource(BRICK, -brick_give);

		//adding the resources that the active player wants
		active.changeResource(WOOD, wood_recieve);
		active.changeResource(WHEAT, wheat_recieve);
		active.changeResource(STONE, stone_recieve);
		active.changeResource(SHEEP, sheep_recieve);
		active.changeResource(BRICK, brick_recieve);

		//adding the resources to the trader that the active player gave
		trader.changeResource(WOOD, wood_give);
		trader.changeResource(WHEAT, wheat_give);
		trader.changeResource(STONE, stone_give);
		trader.changeResource(SHEEP, sheep_give);
		trader.changeResource(BRICK, brick_give);

		//taking away the resources that the trader is giving to the active player
		trader.changeResource(WOOD, -wood_recieve);
		trader.changeResource(WHEAT, -wheat_recieve);
		trader.changeResource(STONE, -stone_recieve);
		trader.changeResource(SHEEP, -sheep_recieve);
		trader.changeResource(BRICK, -brick_recieve);

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
	
		//active = NULL;
		//trader = NULL;
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