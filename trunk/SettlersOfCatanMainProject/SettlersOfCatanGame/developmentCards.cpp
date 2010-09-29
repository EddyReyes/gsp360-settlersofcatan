#include "developmentCards.h"
#include <time.h>
#include <stdlib.h>

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