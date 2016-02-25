#include "equipment.h"

Equipment::Equipment(EquipType type)
	: type(type),
	  name(""),
	  cost(0),
	  quantity(0)
{
	statMods.hpMod=0;
	statMods.apMod=0;
	statMods.dpMod=0;
	statMods.spMod=0;
}

string Equipment::getName()
{
	return name;
}

EquipType Equipment::getType()
{
	return type;
}

int Equipment::getCost()
{
	return cost;
}

StatMod& Equipment::getStatMod()
{
	return statMods;
}

ostream& operator<< (ostream& os, const StatMod& statMods)
{
	os<<" HP: "<<statMods.hpMod
	  <<" AP: "<<statMods.apMod
	  <<" DP: "<<statMods.dpMod
	  <<" SP: "<<statMods.spMod;

	return os;
}

istream& operator>> (istream& is, StatMod& statMods)
{
	is>>statMods.hpMod;
	is>>statMods.apMod;
	is>>statMods.dpMod;
	is>>statMods.spMod;

	return is;
}

istream& operator>> (istream& is, Equipment& equipment)
{
	string junk;

	getline(is, equipment.name);
	is>>equipment.statMods;

	//throwaway new line
	getline(is, junk);
	is>>equipment.cost;

	//throwaway new line
	getline(is, junk);

	return is;
}
