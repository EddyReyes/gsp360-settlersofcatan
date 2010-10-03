#include "tradebank.h"

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

	active = NULL;
	trader = NULL;

	active_set = false;
	trader_set = false;
}

bool TradeBank::setGiveResources(int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick, player* a_active)
{
	active = a_active;

	if(active->getResource(WOOD) < a_wood)
		return false;
	wood_give = a_wood;

	if(active->getResource(WHEAT) < a_wheat)
		return false;
	wheat_give = a_wheat;

	if(active->getResource(STONE) < a_stone)
		return false;
	stone_give = a_stone;

	if(active->getResource(SHEEP) < a_sheep)
		return false;
	sheep_give = a_sheep;

	if(active->getResource(BRICK) < a_brick)
		return false;
	brick_give = a_brick;

	active_set = true;
	return true;
}

bool TradeBank::setRecieveResources(int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick, player* a_trader)
{
	trader = a_trader;

	if(trader->getResource(WOOD) < a_wood)
		return false;
	wood_recieve = a_wood;

	if(trader->getResource(WHEAT) < a_wheat)
		return false;
	wheat_recieve = a_wheat;

	if(trader->getResource(STONE) < a_stone)
		return false;
	stone_recieve = a_stone;

	if(trader->getResource(SHEEP) < a_sheep)
		return false;
	sheep_recieve = a_sheep;

	if(trader->getResource(BRICK) < a_brick)
		return false;
	brick_recieve = a_brick;

	trader_set = true;
	return true;
}

void TradeBank::trade()
{
	if(active_set == true && trader_set == true)//so it wont try to trade to null players
	{
		//taking away the resources that the active player is trading
		active->changeResource(WOOD, -wood_give);
		active->changeResource(WHEAT, -wheat_give);
		active->changeResource(STONE, -stone_give);
		active->changeResource(SHEEP, -sheep_give);
		active->changeResource(BRICK, -brick_give);

		//adding the resources that the active player wants
		active->changeResource(WOOD, wood_recieve);
		active->changeResource(WHEAT, wheat_recieve);
		active->changeResource(STONE, stone_recieve);
		active->changeResource(SHEEP, sheep_recieve);
		active->changeResource(BRICK, brick_recieve);

		//adding the resources to the trader that the active player gave
		trader->changeResource(WOOD, wood_give);
		trader->changeResource(WHEAT, wheat_give);
		trader->changeResource(STONE, stone_give);
		trader->changeResource(SHEEP, sheep_give);
		trader->changeResource(BRICK, brick_give);

		//taking away the resources that the trader is giving to the active player
		trader->changeResource(WOOD, -wood_recieve);
		trader->changeResource(WHEAT, -wheat_recieve);
		trader->changeResource(STONE, -stone_recieve);
		trader->changeResource(SHEEP, -sheep_recieve);
		trader->changeResource(BRICK, -brick_recieve);

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
	
		active = NULL;
		trader = NULL;
		active_set = false;
		trader_set = false;
	}
}

bool TradeBank::tradeWithBank(rsc* resDeck, player* p, char choice_recieve, char choice_give, int num_recieve, char harbor_type)
{
	switch(harbor_type)
	{
	case WOOD:
		if(p->getResource(WOOD) >= 2 * num_recieve)
		{
			p->drawResource(resDeck, choice_recieve, num_recieve);
			p->changeResource(WOOD, -2 * num_recieve);
			resDeck->returnToResourcePool(WOOD, 2 * num_recieve);
			return true;
		}
		break;
	case WHEAT:
		if(p->getResource(WHEAT) >= 2 * num_recieve)
		{
			p->drawResource(resDeck, choice_recieve, num_recieve);
			p->changeResource(WHEAT, -2 * num_recieve);
			resDeck->returnToResourcePool(WHEAT, 2 * num_recieve);
			return true;
		}
		break;
	case STONE:
		if(p->getResource(STONE) >= 2 * num_recieve)
		{
			p->drawResource(resDeck, choice_recieve, num_recieve);
			p->changeResource(STONE, -2 * num_recieve);
			resDeck->returnToResourcePool(STONE, 2 * num_recieve);
			return true;
		}
		break;
	case BRICK:
		if(p->getResource(BRICK) >= 2 * num_recieve)
		{
			p->drawResource(resDeck, choice_recieve, num_recieve);
			p->changeResource(BRICK, -2 * num_recieve);
			resDeck->returnToResourcePool(BRICK, 2 * num_recieve);
			return true;
		}
		break;
	case SHEEP:
		if(p->getResource(SHEEP) >= 2 * num_recieve)
		{
			p->drawResource(resDeck, choice_recieve, num_recieve);
			p->changeResource(SHEEP, -2 * num_recieve);
			resDeck->returnToResourcePool(SHEEP, 2 * num_recieve);
			return true;
		}
		break;
	case THREE_TO_ONE:
		if(p->getResource(choice_give) >= 3 * num_recieve)
		{
			p->drawResource(resDeck, choice_recieve, num_recieve);
			p->changeResource(choice_give, -3 * num_recieve);
			resDeck->returnToResourcePool(choice_give, 3 * num_recieve);
			return true;
		}
	default:
		if(p->getResource(choice_give) >= 4 * num_recieve)
		{
			p->drawResource(resDeck, choice_recieve, num_recieve);
			p->changeResource(choice_give, -4 * num_recieve);
			resDeck->returnToResourcePool(choice_give, 4 * num_recieve);
			return true;
		}
	};
	return false;
}

bool TradeBank::tradeWithBank(rsc* resDeck, player* p, char choice_recieve, char choice_give, int num_recieve)
{
	if(p->getResource(choice_give) >= 4 * num_recieve)
	{
		p->drawResource(resDeck, choice_recieve, num_recieve);
		p->changeResource(choice_give, -4 * num_recieve);
		resDeck->returnToResourcePool(choice_give, 4 * num_recieve);
		return true;
	}
	return false;
}
