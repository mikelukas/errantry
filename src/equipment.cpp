#include <limits>
#include "equipment.h"
#include "streamutils.h"

using std::numeric_limits;
using std::streamsize;

Equipment::Equipment(EquipType type)
	: type(type),
	  name(""),
	  element(none),
	  statMods(NO_STATMOD),
	  effectIds(),
	  cost(0)
{

}

string Equipment::getName() const
{
	return name;
}

Element Equipment::getElement() const
{
	return element;
}

EquipType Equipment::getType() const
{
	return type;
}

int Equipment::getCost() const
{
	return cost;
}

int Equipment::getSellPrice() const
{
	return round(USED_EQUIPMENT_MARKDOWN * ((float) cost));
}

const StatMod& Equipment::getStatMod() const
{
	return statMods;
}

const vector<int>& Equipment::getEffectIds() const
{
	return effectIds;
}

StatMod::StatMod()
	: hpMod(0),
	  mpMod(0),
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
	  <<" MP: "<<statMods.mpMod
	  <<" AP: "<<statMods.apMod
	  <<" DP: "<<statMods.dpMod
	  <<" MDP: "<<statMods.mdpMod
	  <<" SP: "<<statMods.spMod;

	return os;
}

istream& operator>> (istream& is, StatMod& statMods)
{
	is>>statMods.hpMod;
	is>>statMods.mpMod;
	is>>statMods.apMod;
	is>>statMods.dpMod;
	is>>statMods.mdpMod;
	is>>statMods.spMod;

	return is;
}

void operator+= (StatMod& leftMod, const StatMod& rightMod)
{
	leftMod.hpMod += rightMod.hpMod;
	leftMod.mpMod += rightMod.mpMod;
	leftMod.apMod += rightMod.apMod;
	leftMod.dpMod += rightMod.dpMod;
	leftMod.mdpMod += rightMod.mdpMod;
	leftMod.spMod += rightMod.spMod;
}

void operator-= (StatMod& leftMod, const StatMod& rightMod)
{
	leftMod.hpMod -= rightMod.hpMod;
	leftMod.mpMod -= rightMod.mpMod;
	leftMod.apMod -= rightMod.apMod;
	leftMod.dpMod -= rightMod.dpMod;
	leftMod.mdpMod -= rightMod.mdpMod;
	leftMod.spMod -= rightMod.spMod;
}

istream& operator>> (istream& is, Equipment& equipment)
{
	string junk;

	getline(is, equipment.name);

	int elemId;
	is>>elemId;
	equipment.element = static_cast<Element>(elemId);
	is.ignore(numeric_limits<streamsize>::max(), '\n');

	is>>equipment.statMods;
	is.ignore(numeric_limits<streamsize>::max(), '\n');

	getIdLine(is, equipment.effectIds);

	is>>equipment.cost;
	is.ignore(numeric_limits<streamsize>::max(), '\n');

	return is;
}

EquipmentLine::EquipmentLine()
	: pEquipment(NULL),
	  quantity(0)
{

}

EquipmentLine::EquipmentLine(const Equipment* pEquipment)
	: pEquipment(pEquipment),
	  quantity(1)
{

}

EquipmentLine::EquipmentLine(const Equipment* pEquipment, const int quantity)
	: pEquipment(pEquipment),
	  quantity(quantity)
{

}

int EquipmentLine::getTotalCost() const
{
	return pEquipment->getCost() * quantity;
}

int EquipmentLine::getTotalSellPrice() const
{
	return pEquipment->getSellPrice() * quantity;
}

void operator+= (EquipmentLine& leftLine, const EquipmentLine& rightLine)
{
	leftLine.quantity += (rightLine.quantity);
}

void operator-= (EquipmentLine& leftLine, const EquipmentLine& rightLine)
{
	leftLine.quantity -= min(leftLine.quantity, rightLine.quantity); //you can't reduce total equipment to a number below 0
}
