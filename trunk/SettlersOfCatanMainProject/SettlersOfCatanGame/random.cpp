#include <stdlib.h>

int randomColor()
{
	int c = (rand() % 255) | 
			((rand() % 255) << 8) | 
			((rand() % 255) << 16);
	return c;
}