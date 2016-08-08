#ifndef SRC_STATMOD_H_
#define SRC_STATMOD_H_

#include <iostream>

using std::istream;
using std::ostream;

//Encapsulates changes to stats caused by using a piece of equipment
struct StatMod
	{
		int hpMod;
		int maxHpMod;
		int mpMod;
		int maxMpMod;
		int apMod;
		int dpMod;
		int mdpMod;
		int spMod;

		StatMod();

		int getMeltdownDamage() const;

		friend istream& operator>> (istream&, StatMod&);
		friend ostream& operator<< (ostream&, const StatMod&);

		friend void operator+=(StatMod&, const StatMod&);
		friend void operator-=(StatMod&, const StatMod&);
	};
const StatMod NO_STATMOD;

#endif
