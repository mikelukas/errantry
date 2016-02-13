#include "point.h"

istream& operator>> (istream& is, Point& point)
{
	is>>point.x>>point.y;

	return is;
}
