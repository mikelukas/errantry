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
	protected:
		static void displayWeaknessesLineFor(const Character&);
		static void displayStatusesLineFor(const Character&);
		static void displayStatusImmunitiesLineFor(const Character&);

	public:
		static void fullDisplayFor(const Player& player);

		static void battleMainDisplayFor(const Player&);
		static void battleMainDisplayFor(const Monster&);
		static void battleMenuDisplayFor(const Player&);
		static void battleMenuDisplayFor(const Monster&);

		static void equipDisplayFor(Player&);
};

#endif
