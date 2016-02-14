#include "point.h"

int Point::as1dIndex(int maxWidth)
{
	return y*maxWidth + x;
}

istream& operator>> (istream& is, Point& point)
{
	is>>point.x>>point.y;

	return is;
}
