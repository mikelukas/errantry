#include <limits>
#include "character.h"
#include "spell.h"

using std::numeric_limits;
using std::streamsize;

Spell::Spell(istream& is)
	: mpCost(0), //XXX these are to avoid warning about these fields not being inited
	  purchasePrice(0)
{
	getline(is, name);

	int categoryId;
	is>>categoryId;
	category = static_cast<SpellCategory>(categoryId);

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

const SpellCategory Spell::getCategory() const
{
	return category;
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
