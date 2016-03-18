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

	town.loadEquipmentIdLine(is, town.weaponIds);
	town.loadEquipmentIdLine(is, town.armorIds);
	town.loadEquipmentIdLine(is, town.itemIds);

	string convoLine;
	while(getline(is, convoLine) && convoLine != TOWN_CONVO_DELIM) {
		town.conversation += (convoLine + "\n");
	}

	return is;
}

void Town::loadEquipmentIdLine(istream& is, vector<int>& equipIds)
{
	int equipId;
	while(is.peek() != '\n')
	{
		is>>equipId;
		equipIds.push_back(equipId);
	}
	is.get();//throwout newline char
}
