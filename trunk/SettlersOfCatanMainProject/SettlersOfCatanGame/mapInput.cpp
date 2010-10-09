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
		//case map::TRADE:				handleInput_TRADE(e, g);				break;
		case map::BUILDROAD:			handleInput_BUILDROAD(e, g);			break;
		case map::BUILDSETTLEMENT:		handleInput_BUILDSETTLEMENT(e, g);		break;
		case map::BUILDCITY:			handleInput_BUILDCITY(e, g);			break;
		case map::TURNONESETTLEMENT:	handleInput_TURNONESETTLEMENT(e, g);	break;
		case map::TURNONEROAD:			handleInput_TURNONEROAD(e, g);			break;
		case map::TURNTWOSETTLEMENT:	handleInput_TURNTWOSETTLEMENT(e, g);	break;
		case map::TURNTWOROAD:			handleInput_TURNTWOROAD(e, g);			break;
		case map::FREETWORESOURCES:		handleInput_FREETWORESOURCES(e, g);		break;
		case map::FREETWOROADS:			handleInput_FREETWOROADS(e, g);			break;
		case map::SETTHETHIEF:			handleInput_SETTHETHIEF(e, g);			break;
		case map::TRADEBANKHARBORSCREEN:	handleInput_TRADEBANKHARBORSCREEN(e, g);	break;
		case map::TRADETARGET:			handleInput_TRADETARGET(e, g);			break;
		case map::TRADEPLAYERSCREEN:	handleInput_TRADEPLAYERSCREEN(e, g);	break;
		case map::PICKMONOPOLY:			handleInput_PICKMONOPOLY(e, g);	break;
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
			if (myCenters[i].chitWorth == dice1+dice2 && myCenters[i].thiefHere == false)
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
	soundQueue = 20;
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_2:	mapState= map::BUILDCARD;		break;
			case SDLK_3:	mapState= map::RESOURCELIST;	break;
			case SDLK_4:	mapState= map::DEVHAND;			break;
			case SDLK_5:	mapState= map::TRADETARGET;			break;
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
			case SDLK_5:	mapState= map::TRADETARGET;			break;
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
			case SDLK_5:	mapState= map::TRADETARGET;			break;
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
			case SDLK_5:	mapState= map::TRADETARGET;			break;
			case SDLK_m:	if (g->p[g->activePlayer].playDevCard('M'))
							{
								mapState = map::PICKMONOPOLY;
							}
							break;
			case SDLK_s:	if (g->p[g->activePlayer].playDevCard('S'))
							{
								mapState = map::SETTHETHIEF;
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

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void map::handleInput_TRADETARGET(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_1:					
				if (g->activePlayer != 0)
				{	
					tradebank->playerNumber = 0;
					mapState= map::TRADEPLAYERSCREEN;			
				}
				break;
			case SDLK_2:				
				if (g->activePlayer != 1)
				{	
					tradebank->playerNumber = 1;
					mapState= map::TRADEPLAYERSCREEN;			
				}
				break;
			case SDLK_3:				
				if (g->activePlayer != 2)
				{	
					tradebank->playerNumber = 2;
					mapState= map::TRADEPLAYERSCREEN;			
				}
				break;
			case SDLK_4:
				if (g->activePlayer != 3)
				{	
					if (g->numPlayers == 4)
					{
						tradebank->playerNumber = 3;
						mapState= map::TRADEPLAYERSCREEN;			
					}
				}
				break;
			case SDLK_i:
				tradebank->harbor_type = BANK;
				mapState = map::TRADEBANKHARBORSCREEN;			
				break;
			
			case SDLK_b:
				if(g->p[g->activePlayer].ownsBrickHarbor)
				{
					tradebank->harbor_type = BRICK;
					mapState = map::TRADEBANKHARBORSCREEN;	
				}
				else
					cout << "You dont own this harbor type: brick" << endl;
				break;
			
			case SDLK_l:
				if(g->p[g->activePlayer].ownsWoodHarbor)
				{
					tradebank->harbor_type = WOOD;
					mapState = map::TRADEBANKHARBORSCREEN;			
				}
				else
					cout << "You dont own this harbor type: wood" << endl;
				break;
			
			case SDLK_s:	
				if(g->p[g->activePlayer].ownsStoneHarbor)
				{
					tradebank->harbor_type = STONE;
					mapState = map::TRADEBANKHARBORSCREEN;	
				}
				else
					cout << "You dont own this harbor type: stone" << endl;
				break;
			
			case SDLK_e:	
				if(g->p[g->activePlayer].ownsSheepHarbor)
				{
					tradebank->harbor_type = SHEEP;
					mapState = map::TRADEBANKHARBORSCREEN;	
				}
				else
					cout << "You dont own this harbor type: sheep" << endl;
				break;
			
			case SDLK_w:	
				if(g->p[g->activePlayer].ownsWheatHarbor)
				{
					tradebank->harbor_type = WHEAT;
					mapState = map::TRADEBANKHARBORSCREEN;		
				}
				else
					cout << "You dont own this harbor type: wheat" << endl;
				break;
			
			case SDLK_0:	mapState = map::MAP;	break;
			}
	}
}

void map::handleInput_TRADEPLAYERSCREEN(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_0:	mapState= map::MAP;				break;
			case SDLK_1:	mapState= map::MAP;				break;
			case SDLK_2:	mapState= map::BUILDCARD;		break;
			case SDLK_3:	mapState= map::RESOURCELIST;	break;
			case SDLK_4:	mapState= map::DEVHAND;			break;
			
			//i think we could do something like this, it seems to add to the numbers, then when its traded, just set them back to 0
			case SDLK_q:	if (g->p[g->activePlayer].brick > 0 + tradebank->temp_brick_give){tradebank->temp_brick_give++; cout << "+1 Temp Brick Give" << endl;} break;
			case SDLK_w:	if (g->p[g->activePlayer].wood > 0 + tradebank->temp_wood_give){tradebank->temp_wood_give++; cout << "+1 Temp Wood Give" << endl;} break;
			case SDLK_e:	if (g->p[g->activePlayer].stone > 0 + tradebank->temp_stone_give){tradebank->temp_stone_give++; cout << "+1 Temp Stone Give" << endl;} break;
			case SDLK_r:	if (g->p[g->activePlayer].sheep > 0 + tradebank->temp_sheep_give){tradebank->temp_sheep_give++; cout << "+1 Temp Sheep Give" << endl;} break;
			case SDLK_t:	if (g->p[g->activePlayer].wheat > 0 + tradebank->temp_wheat_give){tradebank->temp_wheat_give++; cout << "+1 Temp Wheat Give" << endl;} break;

			case SDLK_a:	if (g->p[tradebank->playerNumber].brick > 0 + tradebank->temp_brick_recieve){tradebank->temp_brick_recieve++; cout << "+1 Temp Brick Recieve" << endl;} break;
			case SDLK_s:	if (g->p[tradebank->playerNumber].wood > 0 + tradebank->temp_wood_recieve){tradebank->temp_wood_recieve++; cout << "+1 Temp Wood Recieve" << endl;} break;
			case SDLK_d:	if (g->p[tradebank->playerNumber].stone > 0 + tradebank->temp_stone_recieve){tradebank->temp_stone_recieve++; cout << "+1 Temp Stone Recieve" << endl;} break;
			case SDLK_f:	if (g->p[tradebank->playerNumber].sheep > 0 + tradebank->temp_sheep_recieve){tradebank->temp_sheep_recieve++; cout << "+1 Temp Sheep Recieve" << endl;} break;
			case SDLK_g:	if (g->p[tradebank->playerNumber].wheat > 0 + tradebank->temp_wheat_recieve){tradebank->temp_wheat_recieve++; cout << "+1 Temp Wheat Recieve" << endl;} break;

			case SDLK_RETURN: 
				if(tradebank->setGiveResources(g) && tradebank->setRecieveResources(g))
				{
					if(tradebank->trade(g))
						cout << "Trade with Player Successful!!" << endl;
					else
						cout << "IT DIDNT WORK!" << endl;
				}
				break;
			case SDLK_BACKSPACE:
				tradebank->ResetBank();
				break;
			}
	}
}

void map::handleInput_TRADEBANKHARBORSCREEN(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_0:	mapState= map::MAP;				break;
			case SDLK_1:	mapState= map::MAP;				break;
			case SDLK_2:	mapState= map::BUILDCARD;		break;
			case SDLK_3:	mapState= map::RESOURCELIST;	break;
			case SDLK_4:	mapState= map::DEVHAND;			break;

			case SDLK_q:	if (g->p[g->activePlayer].brick > 0 + tradebank->temp_brick_give){tradebank->temp_brick_give++; cout << "+1 Temp Brick Give" << endl;} break;
			case SDLK_w:	if (g->p[g->activePlayer].wood > 0 + tradebank->temp_wood_give){tradebank->temp_wood_give++; cout << "+1 Temp Wood Give" << endl;} break;
			case SDLK_e:	if (g->p[g->activePlayer].stone > 0 + tradebank->temp_stone_give){tradebank->temp_stone_give++; cout << "+1 Temp Stone Give" << endl;} break;
			case SDLK_r:	if (g->p[g->activePlayer].sheep > 0 + tradebank->temp_sheep_give){tradebank->temp_sheep_give++; cout << "+1 Temp Sheep Give" << endl;} break;
			case SDLK_t:	if (g->p[g->activePlayer].wheat > 0 + tradebank->temp_wheat_give){tradebank->temp_wheat_give++; cout << "+1 Temp Wheat Give" << endl;} break;

			case SDLK_a:	tradebank->temp_brick_recieve++; cout << "+1 Temp Brick Recieve" << endl; break;
			case SDLK_s:	tradebank->temp_wood_recieve++; cout << "+1 Temp Wood Receive" << endl; break;
			case SDLK_d:	tradebank->temp_stone_recieve++; cout << "+1 Temp Stone Recieve" << endl; break;
			case SDLK_f:	tradebank->temp_sheep_recieve++; cout << "+1 Temp Sheep Recieve" << endl; break;
			case SDLK_g:	tradebank->temp_wheat_recieve++; cout << "+1 Temp Wheat Recieve" << endl; break;
			case SDLK_BACKSPACE: 
				tradebank->ResetBank();
				break;
			case SDLK_RETURN:
				//trading with the bank or harbor
				//player sets the resource they are going to give to something other than 0
				//and sets the number of the amount to recieve to the number they want
				char tgive = ' ';
				char trecieve = ' ';
				int numget = 0;
				char htype = ' ';

				if(tradebank->temp_wood_give != 0)
					tgive = WOOD;
				else if(tradebank->temp_wheat_give != 0)
					tgive = WHEAT;
				else if(tradebank->temp_stone_give != 0)
					tgive = WHEAT;
				else if(tradebank->temp_sheep_give !=0)
					tgive = SHEEP;
				else if(tradebank->temp_brick_give != 0)
					tgive = BRICK;

				if(tradebank->temp_wood_recieve != 0)
				{
					trecieve = WOOD;
					numget = tradebank->temp_wood_recieve;
				}					
				else if(tradebank->temp_wheat_recieve != 0)
				{
					trecieve = WHEAT;
					numget = tradebank->temp_wheat_recieve;
				}
				else if(tradebank->temp_stone_recieve != 0)
				{
					trecieve = STONE;
					numget = tradebank->temp_stone_recieve;
				}
				else if(tradebank->temp_sheep_recieve != 0)
				{
					trecieve = SHEEP;
					numget = tradebank->temp_sheep_recieve;
				}
				else if(tradebank->temp_brick_recieve != 0)
				{
					trecieve = BRICK;
					numget = tradebank->temp_brick_recieve;
				}

				if(tradebank->tradeWithBank(g, trecieve, tgive, numget))
					cout << "Trade with Bank/Harbor Successful!" << endl;
				else
					cout << "Trade with Bank/Harbor Failed!" << endl;

				tradebank->ResetBank();
				tradebank->harbor_type = ' ';
				cout << "Harbor Type Reset" << endl;

				break;
			}
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
void map::handleInput_TRADE(SDL_Event e, Game * g)
{
	//this moved to game so it can be printed to the screen
	//static int wheatactive = 0;
	//static int stoneactive = 0;
	//static int brickactive = 0;
	//static int woodactive = 0;
	//static int sheepactive = 0;

	//static int wheattrader = 0;
	//static int stonetrader = 0;
	//static int bricktrader = 0;
	//static int woodtrader = 0;
	//static int sheeptrader = 0;

	//static int playerNumber = 0;


	//q, w, e, r, t add 1 to the resources that the current player is willing to trade, they are lined up with the pictures
	//a, s, d, f, g add 1 to the resources that the player wants
	//z, x, c, v select the player you want to trade with, z = 1, x = 2, c = 3, v = 4
	//j sets the resources the player will give into the trade bank
	//k sets the resources the player will recieve into the trade bank
	//l completes the trade ( j and k need to be pressed before l should work
	//p prints out what is in the trade bank on the console, dont need this anymore, since now the numbers show up on the trade screen
	//o resets the resources that will go into the trade bank to 0
	//i trades with the bank (i just put a null character in for harbor type for now, but that should be able to take something later


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
			case SDLK_q:	g->brickactive++; cout << "+1 Brick Active Player" << endl; break;
			case SDLK_w:	g->woodactive++; cout << "+1 Wood Active Player" << endl; break;
			case SDLK_e:	g->stoneactive++; cout << "+1 Stone Active Player" << endl; break;
			case SDLK_r:	g->sheepactive++; cout << "+1 Sheep Active Player" << endl; break;
			case SDLK_t:	g->wheatactive++; cout << "+1 Wheat Active Player" << endl; break;

			case SDLK_a:	g->bricktrader++; cout << "+1 Brick Trade Player or Bank" << endl; break;
			case SDLK_s:	g->woodtrader++; cout << "+1 Wood Trade Player or Bank" << endl; break;
			case SDLK_d:	g->stonetrader++; cout << "+1 Stone Trade Player or Bank" << endl; break;
			case SDLK_f:	g->sheeptrader++; cout << "+1 Sheep Trade Player or Bank" << endl; break;
			case SDLK_g:	g->wheattrader++; cout << "+1 Wheat Trade Player or Bank" << endl; break;

			case SDLK_z:	g->playerNumber = 0; cout << "Trade Player set to 1" << endl; break;
			case SDLK_x:	g->playerNumber = 1; cout << "Trade Player set to 2" << endl; break;
			case SDLK_c:	g->playerNumber = 2; cout << "Trade Player set to 3" << endl; break;
			case SDLK_v:	
				if(g->numPlayers == 4)
				{
					g->playerNumber = 3;
					cout << "Trade Player set to 4" << endl;
				}
				else
					cout << "Player 4 doesnt exist" << endl;
				break;

			//setting the resources for trading seems to crash the game, but i dont know why
			//i also couldnt close the console window
			//now it seems that just trying to trade crashes, but the console window closes now
			//this all seems to work now

				//(g, playerNumber, woodtrader, wheattrader, stonetrader, sheeptrader, bricktrader)
			case SDLK_j:
				if(tradebank->setGiveResources(g, int(g->playerNumber), int(g->woodactive), int(g->wheatactive), int(g->stoneactive), int(g->sheepactive), int(g->brickactive)))
					cout << "******Active Player set*******" << endl;
				else
					cout << "Active Player not set" << endl;
				break;

			case SDLK_k:
				if(tradebank->setRecieveResources(g, int(g->playerNumber), int(g->woodtrader), int(g->wheattrader), int(g->stonetrader), int(g->sheeptrader), int(g->bricktrader)))
					cout << "****Trader Set******" << endl;
				else
					cout << "Trader not set" << endl;
				break;

			case SDLK_l:	
				if(tradebank->trade(g, int(g->playerNumber)))
				{
					g->brickactive = 0;
					g->woodactive = 0;
					g->stoneactive = 0;
					g->sheepactive = 0;
					g->wheatactive = 0;

					g->bricktrader = 0;
					g->woodtrader = 0;
					g->stonetrader = 0;
					g->sheeptrader = 0;
					g->wheattrader = 0;

					cout << "Trade with Player Successful!!" << endl;
				}
				else
					cout << "IT DIDNT WORK!" << endl;
				break;
			case SDLK_o:
				g->brickactive = 0;
				g->woodactive = 0;
				g->stoneactive = 0;
				g->sheepactive = 0;
				g->wheatactive = 0;

				g->bricktrader = 0;
				g->woodtrader = 0;
				g->stonetrader = 0;
				g->sheeptrader = 0;
				g->wheattrader = 0;

				cout << "RESOURCES RESET!!!" << endl;
				break;
			case SDLK_p:
				cout << "woodactive:" << g->woodactive << endl;
				cout << "wheatactive:" << g->wheatactive << endl;
				cout << "stoneactive:" << g->stoneactive << endl;
				cout << "sheepactive:" << g->sheepactive << endl; 
				cout << "brickactive:" << g->brickactive << endl;

				cout << "woodtrader:" << g->woodtrader << endl;
				cout << "wheattrader:" << g->wheattrader << endl;
				cout << "stonetrader:" << g->stonetrader << endl;
				cout << "sheeptrader:" << g->sheeptrader << endl; 
				cout << "bricktrader:" << g->bricktrader << endl; 

				cout << "activePlayer from game" << g->activePlayer << endl;
				cout << "trader player num" << g->playerNumber << endl;
				break;

			case SDLK_i:
				//trading with the bank or harbor
				//player sets the resource to something other than 0
				//and sets the number of the amount to recieve to the number they want
				char tgive = ' ';
				char trecieve = ' ';
				int numget = 0;

				if(g->woodactive != 0)
					tgive = WOOD;
				else if(g->wheatactive != 0)
					tgive = WHEAT;
				else if(g->stoneactive != 0)
					tgive = WHEAT;
				else if(g->sheepactive !=0)
					tgive = SHEEP;
				else if(g->brickactive != 0)
					tgive = BRICK;

				if(g->woodtrader != 0)
				{
					trecieve = WOOD;
					numget = g->woodtrader;
				}					
				else if(g->wheattrader != 0)
				{
					trecieve = WHEAT;
					numget = g->wheattrader;
				}
				else if(g->stonetrader != 0)
				{
					trecieve = STONE;
					numget = g->stonetrader;
				}
				else if(g->sheeptrader != 0)
				{
					trecieve = SHEEP;
					numget = g->sheeptrader;
				}
				else if(g->bricktrader != 0)
				{
					trecieve = BRICK;
					numget = g->bricktrader;
				}

				if(tradebank->tradeWithBank(' ', g, trecieve, tgive, numget))
					cout << "Trade with Bank/Harbor Successful!" << endl;
				else
					cout << "Trade with Bank/Harbor Failed!" << endl;

				g->brickactive = 0;
				g->woodactive = 0;
				g->stoneactive = 0;
				g->sheepactive = 0;
				g->wheatactive = 0;

				g->bricktrader = 0;
				g->woodtrader = 0;
				g->stonetrader = 0;
				g->sheeptrader = 0;
				g->wheattrader = 0;
				
				cout << "Resources Reset!" << endl;
				break;
			}
			break;
	}
}
*/

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

void map::handleInput_PICKMONOPOLY(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_b:	playMonopolyCard(BRICK, g);	mapState = map::MAP;	break;
			case SDLK_l:	playMonopolyCard(WOOD, g);	mapState = map::MAP;	break;
			case SDLK_s:	playMonopolyCard(STONE, g);	mapState = map::MAP;	break;
			case SDLK_e:	playMonopolyCard(SHEEP, g);	mapState = map::MAP;	break;
			case SDLK_w:	playMonopolyCard(WHEAT, g);	mapState = map::MAP;	break;	
			}
		break;
	}
}

void map::handleInput_SETTHETHIEF(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichCenterIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	
					if (constructThiefOnMap(g) == true)
					{ 
						thiefIsRolled(g);
						mapState = map::MAP;
					} 
					break;
			}
			break;
	}
}
