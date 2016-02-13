#ifndef _POINT_H_
#define _POINT_H_

#include <istream>

using std::istream;

struct Point
    {
        int x;
        int y;
    };

istream& operator>> (istream&, Point&);

#endif
