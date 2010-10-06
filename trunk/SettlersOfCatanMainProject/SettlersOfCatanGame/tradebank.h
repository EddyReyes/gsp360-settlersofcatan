#pragma once
class Game;
#include "player.h"
#include "stndrd.h"
#include "game.h"

class TradeBank
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

	player active;
	player trader;

	bool active_set;
	bool trader_set;

public:
	TradeBank();
	bool TradeBank::setGiveResources(Game* g, int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick);
	bool TradeBank::setRecieveResources(Game* g, int a_trader_num, int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick);
	bool TradeBank::trade();
	bool TradeBank::tradeWithBank(char harbor_type, Game* g, char choice_recieve, char choice_give, int num_recieve);
	bool TradeBank::tradeWithBank(Game* g, char choice_recieve, char choice_give, int num_recieve);
};