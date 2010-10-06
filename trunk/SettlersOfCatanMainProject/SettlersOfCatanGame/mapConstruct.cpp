#include "map.h"

// THIS CPP IS USED FOR MAP CONSTRUCTION OF NODES AND FINDING EDGES AND SUCH

void map::whichNodeIsWithin(int const & x, int const & y, int radius)
{
	float minDistance, distance, dx, dy, maxRadius = (float)(radius*radius);
	minDistance = 2500;
	Node * closest = NULL;
	for(int i = 0; i < 54; ++i)
	{
		dx = (float)(myNodes[i].pixelX + 16- x);
		dy = (float)(myNodes[i].pixelY + 16 - y);
		distance = dx*dx + dy*dy;
		if(distance < maxRadius 
		&& (closest != NULL || distance < minDistance))
		{
			minDistance = distance;
			nodeSelectron = myNodes[i].ID - 1;
		}
	}
}

void map::whichRoadIsWithin(int const & x, int const & y, int radius)
{
	float minDistance, distance, dx, dy, maxRadius = (float)(radius*radius);
	minDistance = 2500;
	Edge * closest = NULL;
	for(int i = 0; i < 144; ++i)
	{
		dx = (float)(myEdges[i].pixelX + 16 - x);
		dy = (float)(myEdges[i].pixelY + 16 - y);
		distance = dx*dx + dy*dy;
		if(distance < maxRadius 
		&& (closest != NULL || distance < minDistance))
		{
			minDistance = distance;
			roadSelectron = myEdges[i].ID;
		}
	}
}

bool map::constructRoadOnMap(Game * g)
{
	bool buildable = false;

	if (myEdges[roadSelectron].owner == NOT_A_PLAYER && myEdges[roadSelectron].sisterEdge->owner == NOT_A_PLAYER)
	{
		cout << "GETS TO A" << endl;
		if (myEdges[roadSelectron].from->owner == g->p[g->activePlayer].ID || myEdges[roadSelectron].to->owner == g->p[g->activePlayer].ID)
		{
			buildable = true;
			cout << "GETS TO B" << endl;
			//THIS IS TRUE IF EDGE IS OWNERLESS AND TO OR FROM IS PLAYER's, OR TRUE IF SISTER'EDGE IS OWNERLESS AND SISTER'EDGE TO OR SISTER'EDGE FROM IS PLAYER's
		}
		if ( myEdges[roadSelectron].to->owner == NOT_A_PLAYER)
		{
			cout << "GETS TO C" << endl;
			cout << "myEdges[roadSelectron].to->numOfEdges == " << myEdges[roadSelectron].to->numOfEdges << endl;
			for (int i = 0; i < myEdges[roadSelectron].to->numOfEdges; ++i)
			{
				if (myEdges[roadSelectron].to->nodeEdges[i]->owner == g->p[g->activePlayer].ID)
				{
					cout << "GETS TO D" << endl;
					buildable = true;
					//THIS IS TRUE IF EDGE IS OWNERLESS, THE "To's" NODE IS OWNERLESS, AND ONE OF THE "TO's" EDGES IS OWNED BY THE PLAYER
				}
				if (myEdges[roadSelectron].to->nodeEdges[i]->sisterEdge->owner == g->p[g->activePlayer].ID)
				{
					cout << "GETS TO E" << endl;
					buildable = true;
					//THIS IS TRUE IF SISTER'EDGE IS OWNERLESS, THE SISTER'"To's" NODE IS OWNERLESS, AND ONE OF THE SISTER'"TO's" EDGES IS OWNED BY THE PLAYER
				}
			}
		}
		if ( myEdges[roadSelectron].sisterEdge->to->owner == NOT_A_PLAYER)
		{
			cout << "GETS TO F" << endl;
			cout << "myEdges[roadSelectron].sisterEdge->to->numOfEdges == " << myEdges[roadSelectron].sisterEdge->to->numOfEdges << endl;
			for (int i = 0; i < myEdges[roadSelectron].sisterEdge->to->numOfEdges; ++i)
			{
				if (myEdges[roadSelectron].sisterEdge->to->nodeEdges[i]->owner == g->p[g->activePlayer].ID)
				{
					cout << "GETS TO G" << endl;
					buildable = true;
					//THIS IS TRUE IF SISTER'EDGE IS OWNERLESS, THE SISTER'"To's" NODE IS OWNERLESS, AND ONE OF THE SISTER'"TO's" EDGES IS OWNED BY THE PLAYER
				}
				if (myEdges[roadSelectron].sisterEdge->to->nodeEdges[i]->sisterEdge->owner == g->p[g->activePlayer].ID)
				{
					cout << "GETS TO H" << endl;
					buildable = true;
					//THIS IS TRUE IF SISTER'EDGE IS OWNERLESS, THE SISTER'"To's" NODE IS OWNERLESS, AND ONE OF THE SISTER'"TO's" EDGES IS OWNED BY THE PLAYER
				}
			}
		}
		if ( myEdges[roadSelectron].from->owner == NOT_A_PLAYER)
		{
			cout << "GETS TO I" << endl;
			cout << "myEdges[roadSelectron].from->numOfEdges == " << myEdges[roadSelectron].from->numOfEdges << endl;
			for (int i = 0; i < myEdges[roadSelectron].from->numOfEdges; ++i)
			{
				if (myEdges[roadSelectron].from->nodeEdges[i]->owner == g->p[g->activePlayer].ID)
				{
					cout << "GETS TO J" << endl;
					buildable = true;
					//THIS IS TRUE IF EDGE IS OWNERLESS, THE "To's" NODE IS OWNERLESS, AND ONE OF THE "TO's" EDGES IS OWNED BY THE PLAYER
				}
				if (myEdges[roadSelectron].from->nodeEdges[i]->sisterEdge->owner == g->p[g->activePlayer].ID)
				{
					cout << "GETS TO K" << endl;
					buildable = true;
					//THIS IS TRUE IF SISTER'EDGE IS OWNERLESS, THE SISTER'"To's" NODE IS OWNERLESS, AND ONE OF THE SISTER'"TO's" EDGES IS OWNED BY THE PLAYER
				}
			}
		}
		if ( myEdges[roadSelectron].sisterEdge->from->owner == NOT_A_PLAYER)
		{
			cout << "GETS TO L" << endl;
			cout << "myEdges[roadSelectron].sisterEdge->from->numOfEdges " << myEdges[roadSelectron].sisterEdge->from->numOfEdges << endl;
			for (int i = 0; i < myEdges[roadSelectron].sisterEdge->from->numOfEdges; ++i)
			{
				if (myEdges[roadSelectron].sisterEdge->from->nodeEdges[i]->owner == g->p[g->activePlayer].ID)
				{
					cout << "GETS TO M" << endl;
					buildable = true;
					//THIS IS TRUE IF SISTER'EDGE IS OWNERLESS, THE SISTER'"To's" NODE IS OWNERLESS, AND ONE OF THE SISTER'"TO's" EDGES IS OWNED BY THE PLAYER
				}
				if (myEdges[roadSelectron].sisterEdge->from->nodeEdges[i]->sisterEdge->owner == g->p[g->activePlayer].ID)
				{
					cout << "GETS TO N" << endl;
					buildable = true;
					//THIS IS TRUE IF SISTER'EDGE IS OWNERLESS, THE SISTER'"To's" NODE IS OWNERLESS, AND ONE OF THE SISTER'"TO's" EDGES IS OWNED BY THE PLAYER
				}
			}
		}
	}
	if (buildable == true)
	{
		myEdges[roadSelectron].owner = g->p[g->activePlayer].ID;
		return true;
	}
	return false;
}

bool map::constructSettlementOnMap(Game * g)
{
	bool buildable = false;
	for (int i = 0; i < 54; ++i)
	{
		if (nodeSelectron != i)
		{
			if (myNodes[i].owner != 4)
			{
				if							(!(

					((myNodes[i].x + 1 == myNodes[nodeSelectron].x ||
					myNodes[i].x - 1 == myNodes[nodeSelectron].x) 
											&&
					(myNodes[i].y + 1 == myNodes[nodeSelectron].y ||
					myNodes[i].y - 1 == myNodes[nodeSelectron].y)) 
					
											&&


					((myNodes[i].x + 2 == myNodes[nodeSelectron].x ||
					myNodes[i].x - 2 == myNodes[nodeSelectron].x)
											&&
					(myNodes[i].y == myNodes[nodeSelectron].y))
					
											))
				{
					buildable = true;
				}
			}
		}
	}
	for (int i = 0; myNodes[nodeSelectron].numOfEdges; ++i)
	{
		if (myNodes[nodeSelectron].nodeEdges[i]->owner == g->p[g->activePlayer].ID)
		{
			buildable = true;
		}
	}

	if (buildable == true && myNodes[nodeSelectron].owner == 4)
	{
		myNodes[nodeSelectron].owner = g->p[g->activePlayer].ID;
		myNodes[nodeSelectron].cityType = 1;
		return true;
	}
	return false;
}

bool map::constructSettlementOnMapAnywhere(Game * g)
{
	bool buildable = true;
	for (int i = 0; i < 54; ++i)
	{
		if (nodeSelectron != i)
		{
			if (myNodes[i].owner != 4)
			{
				if							(

					((myNodes[i].x + 1 == myNodes[nodeSelectron].x ||
					myNodes[i].x - 1 == myNodes[nodeSelectron].x) 
											&&
					(myNodes[i].y + 1 == myNodes[nodeSelectron].y ||
					myNodes[i].y - 1 == myNodes[nodeSelectron].y)) 
					
											||


					((myNodes[i].x + 2 == myNodes[nodeSelectron].x ||
					myNodes[i].x - 2 == myNodes[nodeSelectron].x)
											&&
					(myNodes[i].y == myNodes[nodeSelectron].y))
					
											)
				{
					buildable = false;
				}
			}
		}
	}
	if (buildable == true && myNodes[nodeSelectron].owner == 4)
	{
		myNodes[nodeSelectron].owner = g->p[g->activePlayer].ID;
		myNodes[nodeSelectron].cityType = 1;
		if( overallTurn == 2 )
		{
			for (int i = 0; i < 19; ++i)
			{
				for (int j = 0; j < 6; ++j)
				{
					if (myCenters[i].connectedNodes[j]->owner == g->p[g->activePlayer].ID)
					{
						if (myNodes[nodeSelectron].ID == myCenters[i].connectedNodes[j]->ID)
						{
							char tempGive = myCenters[i].resource;
							g->p[myCenters[i].connectedNodes[j]->owner].drawResource(&rsc, tempGive, 1);
						}
					}
				}
			}
		}
		return true;
	}
	return false;
}