//im not sure where to put these so they are here for now
/*
void tradeWithHarbor(rsc* resDeck, char harbor_type, Player* p, char choice_recieve, char choice_give)
{
	switch(harbor_type)
	{
	case WOOD:
		if(p->getResource(WOOD) >= 2)
			p->drawResource(resDeck, choice_recieve, 1);
		break;
	case WHEAT:
		if(p->getResource(WHEAT) >= 2)
			p->drawResource(resDeck, choice_recieve, 1);
		break;
	case STONE:
		if(p->getResource(STONE) >= 2)
			p->drawResource(resDeck, choice_recieve, 1);
		break;
	case BRICK:
		if(p->getResource(BRICK) >= 2)
			p->drawResource(resDeck, choice_recieve, 1);
		break;
	case SHEEP:
		if(p->getResource(SHEEP) >= 2)
			p->drawResource(resDeck, choice_recieve, 1);
		break;
	case THREE_TO_ONE:
		if(p->getResource(choice_give) >= 3)
			p->drawResource(resDeck, choice_recieve, 1);
	};
}

void tradeWithBank(rsc* resDeck, Player* p, char choice_recieve, char choice_give)
{
	if(p->getResource(choice_give) >= 4)
		p->drawResource(resDeck, choice_recieve, 1);
}

void tradeWithPlayer(Player* active_player, Player* trade_to_player, char choice_recieve, char choice_give, int num_recieve, int num_give)
{
	if(active_player->getResource(choice_give) >= num_give && trade_to_player->getResource(choice_recieve) >= num_recieve)
	{
		active_player->changeResource(choice_give, -num_give);
		active_player->changeResource(choice_recieve, num_recieve);

		trade_to_player->changeResource(choice_recieve, -num_recieve);
		trade_to_player->changeResource(choice_give, num_give);
	}
}
*/