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

Element getOppositeOf(Element el)
{
	//postcondition: Returns the opposite Element for the given element

	if(el == none)
	{
		return none;
	}

	int opIndex = el % 2 == 0 ? el-1 : el+1;
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
