#include "point.h"

Point::Point()
	: x(0),
	  y(0)
{
}
Point::Point(const Point& other)
	: x(other.x),
	  y(other.y)
{
}
Point::Point(int x, int y)
	: x(x),
	  y(y)
{
}

int Point::as1dIndex(int maxWidth) const
{
	return y*maxWidth + x;
}

istream& operator>> (istream& is, Point& point)
{
	is>>point.x>>point.y;

	return is;
}
