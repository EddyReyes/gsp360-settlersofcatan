#pragma once
#include"stndrd.h"

class rsc
{
private:
	int woodLeft;
	int wheatLeft;
	int stoneLeft;
	int sheepLeft;
	int brickLeft;
public:
	rsc::rsc()
	{
		woodLeft = 19;
		wheatLeft = 19;
		stoneLeft = 19;
		sheepLeft = 19;
		brickLeft = 19;
	}
	int rsc::pullFromResourcePool(char type, int a_num);
	void rsc::returnToResourcePool(char type, int a_num);
};

void rsc::returnToResourcePool(char type, int a_num)
{
	switch(type)
	{
	case WOOD: woodLeft += a_num; break;
	case WHEAT: wheatLeft += a_num; break;
	case STONE: stoneLeft += a_num; break;
	case SHEEP: sheepLeft += a_num; break;
	case BRICK: brickLeft += a_num; break;
	default: break;
	}
}

int rsc::pullFromResourcePool(char type, int a_num)					// THIS FUNCTION TAKES IN A TYPE AND AND AMOUNT OF THAT TYPE (WOOD, 5)
{																	// THEN IT CHECKS IF THERE IS THAT AMOUNT AND IF THERE IS NOT
	int count = 0;													// IT SENDS THE AMOUNT REMAINING. IF IT WAS ASKED FOR 5, AND
	switch (type)													// ONLY 4 REMAIN, IT SETS THE AMOUNT LEFT TO 0 AND RETURNS 4.
	{
	case WOOD: 
		if (a_num <= woodLeft) {woodLeft -= a_num; count = a_num;}
		else { count = woodLeft; woodLeft = 0; }
		break;
	case WHEAT: 
		if (a_num <= wheatLeft) {wheatLeft -= a_num; count = a_num;}
		else { count = wheatLeft; wheatLeft = 0; }
		break;
	case STONE: 
		if (a_num <= stoneLeft) {stoneLeft -= a_num; count = a_num;}
		else { count = stoneLeft; stoneLeft = 0; }
		break;
	case SHEEP: 
		if (a_num <= sheepLeft) {sheepLeft -= a_num; count = a_num;}
		else { count = sheepLeft; sheepLeft = 0; }
		break;
	case BRICK: 
		if (a_num <= brickLeft) {brickLeft -= a_num; count = a_num;}
		else {count = brickLeft; brickLeft = 0; }
		break;
	default: break;
	}
	return count;
}