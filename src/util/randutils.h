#ifndef SRC_UTIL_RANDUTILS_H_
#define SRC_UTIL_RANDUTILS_H_

#include <algorithm> //random_shuffle
#include <set>
#include <vector>

using std::set;
using std::vector;

int getRandIntBetween(int, int);

template <typename T>
vector<T>* shuffleSetIntoVector(const set<T>& setToShuffle)
{
	//postcondition: allocates a new vector of the given set, in random order.
	//vector must be freed by the caller

	vector<T>* shuffledVector = new vector<T>(setToShuffle.begin(), setToShuffle.end());
	std::random_shuffle(shuffledVector->begin(), shuffledVector->end());

	return shuffledVector;
}

#endif
