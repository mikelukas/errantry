#ifndef _POINT_H_
#define _POINT_H_

#include <istream>

using std::istream;

class Point
    {
		public:
			int x;
			int y;

			int as1dIndex(int);
    };

istream& operator>> (istream&, Point&);

#endif
