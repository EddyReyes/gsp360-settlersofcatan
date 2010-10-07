#pragma once
#include <time.h>
#include <stdlib.h>

class dvc
{
private:
	int soldiersLeft;
	int twoRoadsLeft;
	int victoryPointsLeft;
	int monopoliesLeft;
	int yearsOfPlentyLeft;
public:
	dvc::dvc()
	{
		srand((unsigned int)time(0));
		rand();
		soldiersLeft = 14;
		monopoliesLeft = 2;
		victoryPointsLeft = 5;
		twoRoadsLeft = 2;
		yearsOfPlentyLeft = 2;
	}
	bool dvc::drawAvailable(void);
	char dvc::pullCard(void);
	void dvc::initTimeDVC(void);
};

