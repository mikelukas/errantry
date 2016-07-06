#include "element.h"

vector<Element> vectorizeElements()
{
	//postcondition: returns all enum values of Element in a vector, in the same
	//order as they appear in the enum.

	vector<Element> elements;
	elements.push_back(fire);
	elements.push_back(water);
	elements.push_back(air);
	elements.push_back(earth);
	elements.push_back(none);

	return elements;
}

const vector<const Element*>* buildElementPointerVector()
{
	//postcondition: allocates a new vector of pointers to elements in the
	//ELEMENTS vector (mainly to comply w/ Chooser interface).

	vector<const Element*>* elementPtrs = new vector<const Element*>();
	for(int i=0; i < ELEMENTS.size(); i++)
	{
		elementPtrs->push_back(&(ELEMENTS[i]));
	}

	return elementPtrs;
}

Element getOppositeOf(Element el)
{
	//postcondition: Returns the opposite Element for the given element

	if(el == none)
	{
		return none;
	}

	int opIndex = el % 2 == 0 ? el+1 : el-1;
	return ELEMENTS[opIndex];
}

string getDisplayNameFor(Element element)
{
	//postcondition: returns the name of the given Element as a string

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

bool elementCountSort(const pair<Element, int>& elCount1, const pair<Element, int>& elCount2)
{
	//postcondition: sorts element-count pairs by count first, then element ordinal

	if(elCount1.second != elCount2.second)
	{
		return elCount1.second < elCount2.second;
	}
	else
	{
		return elCount1.first < elCount2.first;
	}
};
