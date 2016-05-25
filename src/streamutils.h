#ifndef SRC_STREAMUTILS_H_
#define SRC_STREAMUTILS_H_

#include <istream>
#include <set>
#include <vector>

using std::istream;
using std::set;
using std::vector;

/* Utility methods to unify common code used when reading from streams */

void getIdLine(istream&, set<int>&);
void getIdLine(istream&, vector<int>&);

#endif
