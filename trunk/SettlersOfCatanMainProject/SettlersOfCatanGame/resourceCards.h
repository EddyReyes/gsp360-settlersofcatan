#pragma once
#include "stndrd.h"


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
	//void rsc::DisplayResourceBankStatus(void);
};
