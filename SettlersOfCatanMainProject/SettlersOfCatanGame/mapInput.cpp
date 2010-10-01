#include "map.h"

// DURING THE GAME, THE MAP GOES INTO MANY MAP STATES. 
// THIS IS THE LIST OF ALL THE MAP STATES, AND WHICH 
// INPUT SCRIPT TO CALL WHEN IT IS IN A SPECIFIC MAP STATE.
void map::handleInput(SDL_Event e, player * p)
{
		switch(mapState)
		{
		case map::MAP:					handleInput_MAP(e, p);					break;
		case map::BUILDCARD:			handleInput_BUILDCARD(e, p);			break;
		case map::RESOURCELIST:			handleInput_RESOURCELIST(e, p);			break;
		case map::DEVHAND:				handleInput_DEVHAND(e, p);				break;
		case map::TRADE:				handleInput_TRADE(e, p);				break;
		case map::BUILDROAD:			handleInput_BUILDROAD(e, p);			break;
		case map::BUILDSETTLEMENT:		handleInput_BUILDSETTLEMENT(e, p);		break;
		case map::BUILDCITY:			handleInput_BUILDCITY(e, p);			break;
		case map::TURNONESETTLEMENT:	handleInput_TURNONESETTLEMENT(e, p);	break;
		case map::TURNONEROAD:			handleInput_TURNONEROAD(e, p);			break;
		case map::TURNTWOSETTLEMENT:	handleInput_TURNTWOSETTLEMENT(e, p);	break;
		case map::TURNTWOROAD:			handleInput_TURNTWOROAD(e, p);			break;
		case map::ENDTURN:														break;
		}
}

void map::handleInput_MAP(SDL_Event e, player * p)
{
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
			}
	}
}

void map::handleInput_BUILDCARD(SDL_Event e, player * p)
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
			case SDLK_r:	if (overallTurn == 1 || overallTurn == 2 || p->checkBuildSomething('R', &dvc) == true)
							{
								p->actuallyBuildSomething('R', &rsc, &dvc);
								mapState = map::BUILDROAD;	break;
							}
			case SDLK_s:	if (overallTurn == 1 || overallTurn == 2 || p->checkBuildSomething('S', &dvc) == true)
							{
								p->actuallyBuildSomething('S', &rsc, &dvc);
								mapState = map::BUILDSETTLEMENT;	break;
							}
			case SDLK_c:	if (overallTurn != 1 || overallTurn != 2 || p->checkBuildSomething('C', &dvc) == true)
							{
								p->actuallyBuildSomething('C', &rsc, &dvc);
								mapState = map::BUILDCITY;	break;
							}
			case SDLK_d:	if (overallTurn != 1 || overallTurn != 2 || p->checkBuildSomething('D', &dvc) == true)
							{
								p->actuallyBuildSomething('D', &rsc, &dvc);
								mapState = map::MAP;	break;
							}
			}
	}
}

void map::handleInput_RESOURCELIST(SDL_Event e, player * p)
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

void map::handleInput_DEVHAND(SDL_Event e, player * p)
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
			case SDLK_m:	p->playDevCard('M');			break;
							//MONOPOLY FUNCTIONALITY GO!
			case SDLK_s:	p->playDevCard('S');
							//SOLDIER FUNCTIONALITY GO!
			case SDLK_y:	p->playDevCard('Y');
							//YEAR OF PLENTY FUNCTIONALITY GO!
			case SDLK_t:	p->playDevCard('T');
							//TWO ROADS FUNCTIONALITY GO!
			case SDLK_v:	p->playDevCard('V');
							//VICTORY POINT FUNCTIONALITY GO!
			}
	}
}

void map::handleInput_TRADE(SDL_Event e, player * p)
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
			//ADD TRADE FUNCTIONALITY. DON'T KNOW HOW.
			}
	}
}

void map::handleInput_BUILDROAD(SDL_Event e, player * p)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;

		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT:	if(constructRoadOnMap(p) == true){ mapState = map::MAP;}	break;
			}
			break;
	}
}

void map::handleInput_BUILDSETTLEMENT(SDL_Event e, player * p)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;

		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT:	if(constructSettlementOnMap(p) == true){ mapState = map::MAP;}	break;
			}
			break;
	}
}

void map::handleInput_BUILDCITY(SDL_Event e, player * p)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;
	}
}

void map::handleInput_TURNONESETTLEMENT(SDL_Event e, player * p)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	if(constructSettlementOnMapAnywhere(p) == true){ mapState = map::TURNONEROAD;}	break;
			}
			break;
	}
}

void map::handleInput_TURNONEROAD(SDL_Event e, player * p)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT:	if (constructRoadOnMap(p) == true){ mapState = map::ENDTURN;} break;
			}
			break;
	}
}

void map::handleInput_TURNTWOSETTLEMENT(SDL_Event e, player * p)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:			whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	if(constructSettlementOnMapAnywhere(p) == true){ mapState = map::TURNTWOROAD;}	break;
			}
			break;
	}
}

void map::handleInput_TURNTWOROAD(SDL_Event e, player * p)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	if (constructRoadOnMap(p) == true){ mapState = map::ENDTURN;} break;
			}
			break;
	}
}