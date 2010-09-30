#include "player.h"
#include "stndrd.h"

//this will probably need to go into game, and not map, because currently it needs to get 2 pointers to players
// one way to change it would be to give tradebank a pointer to the array of players.

//for trading in main, we could probably do something like
//if(setGiveResources && setRecieveResources)
//	trade()

//trade does a check now to make sure both the players are set before it trades
TradeBank
{
private:
	int wood_give;
	int wheat_give;
	int stone_give;
	int sheep_give;
	int brick_give;

	int wood_recieve;
	int wheat_recieve;
	int stone_recieve;
	int sheep_recieve;
	int brick_recieve;

	player* active;
	player* trader;

	bool active_set;
	bool trader_set;

public:
	TradeBank();
	bool setGiveResources(int, int, int, int, int, player*);
	bool setRecieveResources(int, int, int, int, int, player*);
	void trade();
};

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

bool setGiveResources(int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick, player* a_active)
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

bool setRecieveResources(int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick, player* a_trader)
{
	trader = a_trade;

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