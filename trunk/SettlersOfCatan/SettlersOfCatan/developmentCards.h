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
};

bool dvc::drawAvailable(void)
{
	if (soldiersLeft + twoRoadsLeft + victoryPointsLeft + monopoliesLeft+ yearsOfPlentyLeft > 0)
	{ return true; }
	else {return false; }
}

char dvc::pullCard(void)
{
	int x = rand() % yearsOfPlentyLeft + soldiersLeft + twoRoadsLeft + victoryPointsLeft + monopoliesLeft + 1;
	if ( x <= yearsOfPlentyLeft ){ yearsOfPlentyLeft--; return 'Y'; }
	else if( x <= soldiersLeft + yearsOfPlentyLeft ){ soldiersLeft--; return 'S'; }
	else if( x <= twoRoadsLeft + soldiersLeft + yearsOfPlentyLeft ){ twoRoadsLeft--; return 'T'; }
	else if( x <= victoryPointsLeft + twoRoadsLeft + soldiersLeft + yearsOfPlentyLeft){ victoryPointsLeft--; return 'V'; }
	else { monopoliesLeft--; return 'M'; }
}