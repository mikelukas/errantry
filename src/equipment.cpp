#include "equipment.h"

Equipment::Equipment(EquipType type)
	: type(type),
	  name(""),
	  cost(0)
{
	statMods.hpMod=0;
	statMods.apMod=0;
	statMods.dpMod=0;
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

const StatMod& Equipment::getStatMod() const
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

void operator+= (EquipmentLine& leftLine, const EquipmentLine& rightLine)
{
	leftLine.quantity += (rightLine.quantity);
}
