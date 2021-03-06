#ifndef _POINT_H_
#define _POINT_H_

#include <istream>

using std::istream;

class Point
    {
		public:
			int x;
			int y;

			Point();
			Point(const Point&);
			Point(int, int);

			int as1dIndex(int) const;
    };

istream& operator>> (istream&, Point&);

#endif
