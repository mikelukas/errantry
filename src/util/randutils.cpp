#include "randutils.h"

#include <stdlib.h>

int getRandIntBetween(int start, int end)
{
	//postcondition: returns a random int between start and end, inclusive

	return rand() % (end+1-start) + start;
}
