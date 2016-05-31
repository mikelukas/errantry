#include "equipment.h"

Equipment::Equipment(EquipType type)
	: type(type),
	  name(""),
	  cost(0)
{
	statMods.hpMod=0;
	statMods.mpMod=0;
	statMods.apMod=0;
	statMods.dpMod=0;
	statMods.mdpMod=0;
	statMods.spMod=0;
}

string Equipment::getName() const
{
	return name;
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

StatMod::StatMod()
	: hpMod(0),
	  mpMod(0),
	  apMod(0),
	  dpMod(0),
	  mdpMod(0),
	  spMod(0)
{

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
