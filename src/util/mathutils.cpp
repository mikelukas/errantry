#include <math.h>
#include "mathutils.h"

double roundDouble(double toRound)
{
	//postcondition: returns toRound rounded to the 1's place, returned as a double
	return floor(toRound + 0.5);
}

int roundInt(double toRound)
{
	//postcondition: returns toRound rounded to the nearest integer, returned as
	//an int.  Because of this, ensure that toRound fits within an int.
	return (int) roundDouble(toRound);
}

int max(int left, int right)
{
	//postcondition: returns left if left is greater than or equal to right
	return left >= right ? left : right;
}
