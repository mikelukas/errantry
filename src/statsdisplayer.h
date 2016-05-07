#ifndef SRC_STATSDISPLAYER_H_
#define SRC_STATSDISPLAYER_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include "monster.h"
#include "player.h"

using std::cout;
using std::endl;
using std::ostringstream;
using std::setw;

class StatsDisplayer
{
	public:
		static void fullDisplayFor(const Player& player);
		static void battleDisplayFor(const Player&);
		static void battleDisplayFor(const Monster&);
};

#endif
