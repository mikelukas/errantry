#include "statmod.h"

StatMod::StatMod()
	: hpMod(0),
	  maxHpMod(0),
	  mpMod(0),
	  maxMpMod(0),
	  apMod(0),
	  dpMod(0),
	  mdpMod(0),
	  spMod(0)
{

}

int StatMod::getMeltdownDamage() const
{
	return hpMod + mpMod + apMod + dpMod + mdpMod + spMod;
}

ostream& operator<< (ostream& os, const StatMod& statMods)
{
	os<<" HP: "<<statMods.hpMod
	  <<" Max HP: "<<statMods.maxHpMod
	  <<" MP: "<<statMods.mpMod
	  <<" Max MP: "<<statMods.maxMpMod
	  <<" AP: "<<statMods.apMod
	  <<" DP: "<<statMods.dpMod
	  <<" MDP: "<<statMods.mdpMod
	  <<" SP: "<<statMods.spMod;

	return os;
}

istream& operator>> (istream& is, StatMod& statMods)
{
	is>>statMods.hpMod;
	is>>statMods.maxHpMod;
	is>>statMods.mpMod;
	is>>statMods.maxMpMod;
	is>>statMods.apMod;
	is>>statMods.dpMod;
	is>>statMods.mdpMod;
	is>>statMods.spMod;

	return is;
}

void operator+= (StatMod& leftMod, const StatMod& rightMod)
{
	leftMod.hpMod += rightMod.hpMod;
	leftMod.maxHpMod += rightMod.maxHpMod;
	leftMod.mpMod += rightMod.mpMod;
	leftMod.maxMpMod += rightMod.maxMpMod;
	leftMod.apMod += rightMod.apMod;
	leftMod.dpMod += rightMod.dpMod;
	leftMod.mdpMod += rightMod.mdpMod;
	leftMod.spMod += rightMod.spMod;
}

void operator-= (StatMod& leftMod, const StatMod& rightMod)
{
	leftMod.hpMod -= rightMod.hpMod;
	leftMod.maxHpMod -= rightMod.maxHpMod;
	leftMod.mpMod -= rightMod.mpMod;
	leftMod.maxMpMod -= rightMod.maxMpMod;
	leftMod.apMod -= rightMod.apMod;
	leftMod.dpMod -= rightMod.dpMod;
	leftMod.mdpMod -= rightMod.mdpMod;
	leftMod.spMod -= rightMod.spMod;
}

