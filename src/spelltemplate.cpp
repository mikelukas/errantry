#include "spelltemplate.h"

#include <limits>
#include "character.h"

using std::numeric_limits;
using std::streamsize;

SpellTemplate::SpellTemplate(istream& is)
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

const string& SpellTemplate::getName() const
{
	return name;
}

const SpellCategory SpellTemplate::getCategory() const
{
	return category;
}

const Element SpellTemplate::getElement() const
{
	return element;
}

const int SpellTemplate::getMpCost() const
{
	return mpCost;
}
const int SpellTemplate::getPurchasePrice() const
{
	return purchasePrice;
}

const set<int>& SpellTemplate::getEligibleLocations() const
{
	return eligibleLocations;
}

const set<int>& SpellTemplate::getEligibleTargets() const
{
	return eligibleTargets;
}
