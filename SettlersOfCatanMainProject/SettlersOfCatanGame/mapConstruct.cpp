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

	if (myEdges[roadSelectron].owner == 4)
	{
		//cout << "got to 1" << endl;
		if (myEdges[roadSelectron].from->owner == g->p[g->activePlayer].ID || myEdges[roadSelectron].to->owner == g->p[g->activePlayer].ID)
		{
			buildable = true;
			//cout << "got to 2b (FINISH)" << endl;
		}
		else if ( myEdges[roadSelectron].to->owner == 4)
		{
			//cout << "got to 2a" << endl;
			for (int i = 0; i < myEdges[roadSelectron].to->numOfEdges; ++i)
			{
				//cout << "got to 3a" << endl;
				if (myEdges[roadSelectron].to->nodeEdges[i]->owner == g->p[g->activePlayer].ID)
				{
					//cout << "got to 4a FINISH" << endl;
					buildable = true;
				}
			}
		}
		else if ( myEdges[roadSelectron].from->owner == 4)
		{
			//cout << "got to 2c" << endl;
			for (int i = 0; i < myEdges[roadSelectron].to->numOfEdges; ++i)
			{
				//cout << "got to 3c" << endl;
				if (myEdges[roadSelectron].from->nodeEdges[i]->owner == g->p[g->activePlayer].ID)
				{
					//cout << "got to 4c FINISH" << endl;
					buildable = true;
				}
			}
		}
		
		
		if (buildable == true)
		{
			//cout << "got to BUILD!" << endl;
			myEdges[roadSelectron].owner = g->p[g->activePlayer].ID;
			return true;
		}
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