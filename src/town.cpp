#include "town.h"

string Town::getName() const
{
	return name;
}

Point Town::getLocation() const
{
	return location;
}

vector<int> Town::getShopEquipmentIds(EquipType equipType) const
{
	switch(equipType)
	{
	case WEAPON:
		return weaponIds;
		break;
	case ARMOR:
		return armorIds;
		break;
	case ITEM:
		return itemIds;
		break;
	default:
		return vector<int>();
		break;
	}
}

vector<int> Town::getShopSpellIds() const
{
	return spellIds;
}

string Town::getConversation() const
{
	//postcondition: returns conversation text to be displayed when user
	//chooses Talk when in a town.

	return conversation;
}

istream& operator>> (istream& is, Town& town)
{
	//Precondition: assumes input stream contains enough data to fully populate
	//a single town object.
	//Postcondition: populates town reference with data read from input stream,
	//and returns the stream.  Closing of the stream is left to the caller.

	getline(is,town.name);
	is>>town.location;
	is.get(); //gets the newline character after the location point is read in

	getIdLine(is, town.weaponIds);
	getIdLine(is, town.armorIds);
	getIdLine(is, town.itemIds);
	getIdLine(is, town.spellIds);

	string convoLine;
	while(getline(is, convoLine) && convoLine != TOWN_CONVO_DELIM) {
		town.conversation += (convoLine + "\n");
	}

	return is;
}
