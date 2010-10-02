#pragma once

#include "player.h"
#include "stndrd.h"

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

	player* active;
	player* trader;

	bool active_set;
	bool trader_set;

public:
	TradeBank();
	bool setGiveResources(int, int, int, int, int, player*);
	bool setRecieveResources(int, int, int, int, int, player*);
	void trade();
	bool tradeWithBank(rsc* resDeck, player* p, char choice_recieve, char choice_give, int num_recieve, char harbor_type);
	bool tradeWithBank(rsc* resDeck, player* p, char choice_recieve, char choice_give, int num_recieve);
};