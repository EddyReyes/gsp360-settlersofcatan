#include "map.h"
#include <ctime>

// DURING THE GAME, THE MAP GOES INTO MANY MAP STATES. 
// THIS IS THE LIST OF ALL THE MAP STATES, AND WHICH 
// INPUT SCRIPT TO CALL WHEN IT IS IN A SPECIFIC MAP STATE.

void map::handleInput(SDL_Event e, Game * g)
{
		switch(mapState)
		{
		case map::BEGINTURN:			handleInput_BEGINTURN(e, g);			break;		
		case map::MAP:					handleInput_MAP(e, g);					break;
		case map::BUILDCARD:			handleInput_BUILDCARD(e, g);			break;
		case map::RESOURCELIST:			handleInput_RESOURCELIST(e, g);			break;
		case map::DEVHAND:				handleInput_DEVHAND(e, g);				break;
		case map::TRADE:				handleInput_TRADE(e, g);				break;
		case map::BUILDROAD:			handleInput_BUILDROAD(e, g);			break;
		case map::BUILDSETTLEMENT:		handleInput_BUILDSETTLEMENT(e, g);		break;
		case map::BUILDCITY:			handleInput_BUILDCITY(e, g);			break;
		case map::TURNONESETTLEMENT:	handleInput_TURNONESETTLEMENT(e, g);	break;
		case map::TURNONEROAD:			handleInput_TURNONEROAD(e, g);			break;
		case map::TURNTWOSETTLEMENT:	handleInput_TURNTWOSETTLEMENT(e, g);	break;
		case map::TURNTWOROAD:			handleInput_TURNTWOROAD(e, g);			break;
		case map::FREETWORESOURCES:		handleInput_FREETWORESOURCES(e, g);		break;
		case map::FREETWOROADS:			handleInput_FREETWOROADS(e,g );			break;
		case map::ENDTURN:														break;
		}
}

void map::handleInput_BEGINTURN(SDL_Event e, Game * g)
{
	if (rolledDice == false)
	{
		cout << " ROLLED A " << dice1+dice2 << endl;
		for (int i = 0; i < 19; ++i)
		{
			if (myCenters[i].chitWorth == dice1+dice2)
			{
				for (int j = 0; j < 6; ++j)
				{
					if (myCenters[i].connectedNodes[j]->owner != map::NOT_A_PLAYER)
					{
						int amount = myCenters[i].connectedNodes[j]->cityType;
						char type = myCenters[i].resource;
						g->p[myCenters[i].connectedNodes[j]->owner].drawResource(&rsc, type, amount);
						cout << "AWARDED " << amount << " " << type << " to player " << g->p[myCenters[i].connectedNodes[j]->owner].ID << endl;
					}
				}
			}
		}
		rsc.DisplayResourceBankStatus();
	}
	rolledDice = true;
	


	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_SPACE:		rolledDice = false; 
									mapState= map::MAP;		break;	// THIS SWITCH FUNCTION MEANS THAT THIS 
																	// STATE WILL WAIT UNTIL THE PLAYER ACKNOWLEDGES 
																	// THE FACT THAT IT IS HIS OR HER TURN AND HE OR 
																	// SHE HAS ROLLED A #.
			}
	}
}

void map::handleInput_MAP(SDL_Event e, Game * g)
{
	placeholderFREE = 2; // POOR PLACEMENT, BUT IT MUST BE DONE!
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_2:	mapState= map::BUILDCARD;		break;
			case SDLK_3:	mapState= map::RESOURCELIST;	break;
			case SDLK_4:	mapState= map::DEVHAND;			break;
			case SDLK_5:	mapState= map::TRADE;			break;
			case SDLK_0:	mapState= map::ENDTURN;			break;
				//Dice roll can go here <--------------------
				// kyle:: actually I'd recommend putting it in handleInput_BEGINTURN, 
				// that way it only happens once. handleInput_MAP can happen multiple 
				// times per turn (if someone switches in and out of the map screen 
				// and the trade screen, for example).
			}
	}
}

void map::handleInput_BUILDCARD(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_1:	mapState= map::MAP;				break;
			case SDLK_3:	mapState= map::RESOURCELIST;	break;
			case SDLK_4:	mapState= map::DEVHAND;			break;
			case SDLK_5:	mapState= map::TRADE;			break;
			case SDLK_0:	mapState= map::ENDTURN;			break;
			case SDLK_r:	if (g->p[g->activePlayer].checkBuildSomething('R', &dvc) == true)
							{
								mapState = map::BUILDROAD;	break;
							}
			case SDLK_s:	if (g->p[g->activePlayer].checkBuildSomething('S', &dvc) == true)
							{
								mapState = map::BUILDSETTLEMENT;	break;
							}
			case SDLK_c:	if (g->p[g->activePlayer].checkBuildSomething('C', &dvc) == true)
							{
								mapState = map::BUILDCITY;	break;
							}
			case SDLK_d:	if (g->p[g->activePlayer].checkBuildSomething('D', &dvc) == true)
							{
								g->p[g->activePlayer].actuallyBuildSomething('D', &rsc, &dvc);
								mapState = map::MAP;	break;
							}
			}
	}
}

void map::handleInput_RESOURCELIST(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_1:	mapState= map::MAP;				break;
			case SDLK_2:	mapState= map::BUILDCARD;		break;
			case SDLK_4:	mapState= map::DEVHAND;			break;
			case SDLK_5:	mapState= map::TRADE;			break;
			}
	}
}

void map::handleInput_DEVHAND(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_1:	mapState= map::MAP;				break;
			case SDLK_2:	mapState= map::BUILDCARD;		break;
			case SDLK_3:	mapState= map::RESOURCELIST;	break;
			case SDLK_5:	mapState= map::TRADE;			break;
			case SDLK_m:	if (g->p[g->activePlayer].playDevCard('M'))
							{
								//MONOPOLY FUNCTIONALITY GO!
							}
							break;
			case SDLK_s:	if (g->p[g->activePlayer].playDevCard('S'))
							{
								//SOLDIER FUNCTIONALITY GO!
							}
							break;
			case SDLK_y:	if (g->p[g->activePlayer].playDevCard('Y'))
							{	
								mapState = map::FREETWORESOURCES;
							}
							break;
			case SDLK_r:	if (g->p[g->activePlayer].playDevCard('T'))
							{
								mapState = map::FREETWOROADS;
							}
							break;
			case SDLK_v:	if (g->p[g->activePlayer].playDevCard('V'))
							{
								mapState= map::MAP;
							}
							break;
							
			}
	}
}

void map::handleInput_TRADE(SDL_Event e, Game * g)
{
	static int wheatactive = 0;
	static int stoneactive = 0;
	static int brickactive = 0;
	static int woodactive = 0;
	static int sheepactive = 0;

	static int wheattrader = 0;
	static int stonetrader = 0;
	static int bricktrader = 0;
	static int woodtrader = 0;
	static int sheeptrader = 0;

	int playerNumber = 0;

	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_1:	mapState= map::MAP;				break;
			case SDLK_2:	mapState= map::BUILDCARD;		break;
			case SDLK_3:	mapState= map::RESOURCELIST;	break;
			case SDLK_4:	mapState= map::DEVHAND;			break;
			//ADD TRADE FUNCTIONALITY. DON'T KNOW HOW.
			
			//i think we could do something like this, it seems to add to the numbers, then when its traded, just set them back to 0
			case SDLK_q:	brickactive++; break;
			case SDLK_w:	woodactive++; break;
			case SDLK_e:	stoneactive++; break;
			case SDLK_r:	sheepactive++; break;
			case SDLK_t:	wheatactive++; break;

			case SDLK_a:	bricktrader++; break;
			case SDLK_s:	woodtrader++; break;
			case SDLK_d:	stonetrader++; break;
			case SDLK_f:	sheeptrader++; break;
			case SDLK_g:	wheattrader++; break;

			case SDLK_z:	playerNumber = 0; break;
			case SDLK_x:	playerNumber = 1; break;
			case SDLK_c:	playerNumber = 2; break;
			case SDLK_v:	playerNumber = 3; break;

			//bool TradeBank::setGiveResources(Game* g, int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick);
			//bool TradeBank::setRecieveResources(Game* g, int a_trader_num, int a_wood, int a_wheat, int a_stone, int a_sheep, int a_brick);

				//setting the resources for trading seems to crash the game, but i dont know why
				//i also couldnt close the console window
			case SDLK_j:/*	
				if(tradebank->setGiveResources(g, woodactive, wheatactive, stoneactive, sheepactive, brickactive))
					cout << "Active Player set!!" << endl;
				else
					cout << "Active Player not set!!" << endl;
				break;*/

			case SDLK_k:/*	
				if(tradebank->setRecieveResources(g, playerNumber, woodtrader, wheattrader, stonetrader, sheeptrader, bricktrader))
					cout << "Trader Set!!" << endl;
				else
					cout << "Trader not set!!!" << endl;
				break;*/

			case SDLK_l:	
				//if(tradebank->trade())
				{
					woodactive = 0;
					wheatactive = 0;
					stoneactive = 0;
					sheepactive = 0;
					brickactive = 0;

					woodtrader = 0;
					wheattrader = 0;
					stonetrader = 0;
					sheeptrader = 0;
					bricktrader = 0;
				}
				break;
			case SDLK_p:
				cout << woodactive << endl;
				cout << wheatactive << endl;
				cout << stoneactive << endl;
				cout << sheepactive << endl; 
				cout << brickactive << endl; 

				cout << woodtrader << endl; 
				cout << wheattrader << endl; 
				cout << stonetrader << endl; 
				cout << sheeptrader << endl; 
				cout << bricktrader << endl; break;
			}
			break;
	}
}

void map::handleInput_BUILDROAD(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;

		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT:	
				if(constructRoadOnMap(g) == true)
				{ 
					g->p[g->activePlayer].actuallyBuildSomething('R', &rsc, &dvc);
					if (calculateVictoryPoints(g))
					{
						mapState = map::SOMEONEWON;
					}
					else
					{
						mapState = map::MAP;
					}
				}	
				break;
			}
			break;

		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_0:	mapState= map::MAP;				break;
			}
			break;
	}
}

void map::handleInput_BUILDSETTLEMENT(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;

		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT:	
				if(constructSettlementOnMap(g) == true)
				{ 
					g->p[g->activePlayer].actuallyBuildSomething('S', &rsc, &dvc);
					if (calculateVictoryPoints(g))
					{
						mapState = map::SOMEONEWON;
					}
					else
					{
						mapState = map::MAP;
					}
				}	
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_0:	mapState= map::MAP;				break;
			}
			break;
	}
}

void map::handleInput_BUILDCITY(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;

		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT:	
				if(constructCityOnMap(g) == true)
				{ 
					g->p[g->activePlayer].actuallyBuildSomething('C', &rsc, &dvc);
					if (calculateVictoryPoints(g))
					{
						mapState = map::SOMEONEWON;
					}
					else
					{
						mapState = map::MAP;
					}
				}	
				break;
			}
			break;

		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_0:	mapState= map::MAP;				break;
			}
			break;
	}
}

void map::handleInput_TURNONESETTLEMENT(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	
					if(constructSettlementOnMapAnywhere(g) == true)
					{ 
						g->p[g->activePlayer].freeBuildSomething('S', &rsc, &dvc);
						mapState = map::TURNONEROAD;
					}	
					break;
			}
			break;
	}
}

void map::handleInput_TURNONEROAD(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT:	
				if (constructRoadOnMap(g) == true)
				{ 
					g->p[g->activePlayer].freeBuildSomething('R', &rsc, &dvc);
					mapState = map::ENDTURN;
				} 
				break;
			}
			break;
	}
}

void map::handleInput_TURNTWOSETTLEMENT(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:			whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	
					if(constructSettlementOnMapAnywhere(g) == true)
					{ 
						g->p[g->activePlayer].freeBuildSomething('S', &rsc, &dvc);
						mapState = map::TURNTWOROAD;
					}	
					break;
			}
			break;
	}
}

void map::handleInput_TURNTWOROAD(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	
					if (constructRoadOnMap(g) == true)
					{ 
						g->p[g->activePlayer].freeBuildSomething('R', &rsc, &dvc);
						mapState = map::ENDTURN;
					} 
					break;
			}
			break;
	}
}

void map::handleInput_FREETWOROADS(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	
					if (constructRoadOnMap(g) == true)
					{ 
						g->p[g->activePlayer].freeBuildSomething('R', &rsc, &dvc);
						placeholderFREE--;
					} 
					break;
			}
			break;
	}
	if (placeholderFREE == 0)
	{
		mapState = map::MAP;
	}
}

void map::handleInput_FREETWORESOURCES(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_b:	g->p[g->activePlayer].drawResource(&rsc, BRICK, 1);	placeholderFREE--;			break;		
			case SDLK_l:	g->p[g->activePlayer].drawResource(&rsc, WOOD, 1);	placeholderFREE--;			break;	
			case SDLK_s:	g->p[g->activePlayer].drawResource(&rsc, STONE, 1); placeholderFREE--;			break;	
			case SDLK_e:	g->p[g->activePlayer].drawResource(&rsc, SHEEP, 1);	placeholderFREE--;			break;	
			case SDLK_w:	g->p[g->activePlayer].drawResource(&rsc, WHEAT, 1);	placeholderFREE--;			break;	
			}
		break;
	}
	if (placeholderFREE == 0)
	{
		mapState = map::MAP;
	}
}