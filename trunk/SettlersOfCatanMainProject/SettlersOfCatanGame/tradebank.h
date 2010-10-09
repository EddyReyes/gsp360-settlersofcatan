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

	bool active_set;
	bool trader_set;

public:
	int temp_wood_give;
	int temp_wheat_give;
	int temp_stone_give;
	int temp_sheep_give;
	int temp_brick_give;

	int temp_wood_recieve;
	int temp_wheat_recieve;
	int temp_stone_recieve;
	int temp_sheep_recieve;
	int temp_brick_recieve;

	int playerNumber;//trader player number

	char harbor_type;

	TradeBank();
	//new functions, that use things in the trade bank
	bool TradeBank::setGiveResources(Game* g);
	bool TradeBank::setRecieveResources(Game* g);
	bool TradeBank::trade(Game* g);
	bool TradeBank::tradeWithBank(Game* g, char choice_recieve, char choice_give, int num_recieve);
	void TradeBank::ResetBank();

	bool TradeBank::setGiveResources(Game* g, int a_trader_num, int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick);
	bool TradeBank::setRecieveResources(Game* g, int a_trader_num, int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick);
	bool TradeBank::trade(Game* g, int a_trader_num);
	bool TradeBank::tradeWithBank(char harbor_type, Game* g, char choice_recieve, char choice_give, int num_recieve);
};