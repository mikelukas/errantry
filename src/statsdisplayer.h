#ifndef SRC_STATSDISPLAYER_H_
#define SRC_STATSDISPLAYER_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include "player.h"

using std::cout;
using std::endl;
using std::ostringstream;
using std::setw;

class StatsDisplayer
{
	public:
		static void fullDisplayFor(const Player& player);
};

#endif
