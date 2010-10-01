#include "map.h"

// THIS CPP IS USED FOR MAP CONSTRUCTION OF NODES AND FINDING EDGES AND SUCH

void map::whichNodeIsWithin(int const & x, int const & y, int radius)
{
	float minDistance, distance, dx, dy, maxRadius = radius*radius;
	minDistance = 2500;
	Node * closest = NULL;
	for(int i = 0; i < 54; ++i)
	{
		dx = myNodes[i].pixelX + 16- x;
		dy = myNodes[i].pixelY + 16 - y;
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
	float minDistance, distance, dx, dy, maxRadius = radius*radius;
	minDistance = 2500;
	Edge * closest = NULL;
	for(int i = 0; i < 144; ++i)
	{
		dx = myEdges[i].pixelX + 16 - x;
		dy = myEdges[i].pixelY + 16 - y;
		distance = dx*dx + dy*dy;
		if(distance < maxRadius 
		&& (closest != NULL || distance < minDistance))
		{
			minDistance = distance;
			roadSelectron = myEdges[i].ID;
		}
	}
}

bool map::constructRoadOnMap(player * p)
{
	bool buildable = false;

	if (myEdges[roadSelectron].owner == 4)
	{
		//cout << "got to 1" << endl;
		if (myEdges[roadSelectron].from->owner == p->ID || myEdges[roadSelectron].to->owner == p->ID)
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
				if (myEdges[roadSelectron].to->nodeEdges[i]->owner == p->ID)
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
				if (myEdges[roadSelectron].from->nodeEdges[i]->owner == p->ID)
				{
					//cout << "got to 4c FINISH" << endl;
					buildable = true;
				}
			}
		}
		
		
		if (buildable == true)
		{
			//cout << "got to BUILD!" << endl;
			myEdges[roadSelectron].owner = p->ID;
			return true;
		}
	}
	return false;
}

bool map::constructSettlementOnMap(player * p)
{
	//THIS FUNCTION IS MILDLY BAD. IT LOOKS FOR BUILDABILITY BY DRAW PIXEL COUNTS, NOT BY ACTUALLY LOOKING AT EDGES THAT CONNECT TO NODES.
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
	// RIGHT AROUND HERE, THIS FUNCTION WOULD NEED TO CHECK FOR ROADS AND SET BUILDABILITY TO FALSE IF IT FINDS NONE.

	for (int i = 0; myNodes[nodeSelectron].numOfEdges; ++i)
	{
		if (myNodes[nodeSelectron].nodeEdges[i]->owner == p->ID)
		{
			buildable = true;
		}
	}

	if (buildable == true && myNodes[nodeSelectron].owner == 4)
	{
		myNodes[nodeSelectron].owner = p->ID;
		myNodes[nodeSelectron].cityType = 1;
		return true;
	}
	return false;
}

bool map::constructSettlementOnMapAnywhere(player * p)
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
		myNodes[nodeSelectron].owner = p->ID;
		myNodes[nodeSelectron].cityType = 1;
		return true;
	}
	return false;
}