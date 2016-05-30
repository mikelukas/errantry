#include <limits>
#include "spell.h"

using std::numeric_limits;
using std::streamsize;

Spell::Spell(istream& is)
	: mpCost(0), //XXX these are to avoid warning about these fields not being inited
	  purchasePrice(0)
{
	getline(is, name);

	int elemId;
	is>>elemId;
	element = static_cast<Element>(elemId);

	is>>mpCost;
	is>>purchasePrice;
	is.ignore(numeric_limits<streamsize>::max(), '\n');

	getIdLine(is, eligibleLocations);
	getIdLine(is, eligibleTargets);

	getIdLine(is, effectIds);
}

const string& Spell::getName() const
{
	return name;
}

const Element Spell::getElement() const
{
	return element;
}

const int Spell::getMpCost() const
{
	return mpCost;
}
const int Spell::getPurchasePrice() const
{
	return purchasePrice;
}

const set<int>& Spell::getEligibleLocations() const
{
	return eligibleLocations;
}

const set<int>& Spell::getEligibleTargets() const
{
	return eligibleTargets;
}

void Spell::cast(Character& caster, Character& target) const
{
	//postcondition: //The caster's MP is then reduced by the mpCost of the spell,
	//and the effect function of each effect referenced by this spell is called,
	//in order (dat file specifies order), with the caster and target.

	//TODO: reduce caster MP

	for(vector<int>::const_iterator it = effectIds.begin(); it != effectIds.end(); it++)
	{
		(*EFFECTS[*it])(caster, target);
	}
}

string getDisplayNameFor(Element element)
{
	switch(element)
	{
	case fire:
		return "Fire";
	case earth:
		return "Earth";
	case air:
		return "Air";
	case water:
		return "Water";

	default:
		return "Non-elemental";
	}
}
