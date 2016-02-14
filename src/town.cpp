#include "town.h"

string Town::getName()
{
	return name;
}

Point Town::getLocation()
{
	return location;
}

string Town::getConversation()
{
	return conversation;
}

istream& operator>> (istream& is, Town& town)
{
	getline(is,town.name);
	is>>town.location;

	string convoLine;
	getline(is,convoLine); //gets the newline character after the location point is read in

	while(getline(is, convoLine) && convoLine != TOWN_CONVO_DELIM) {
		town.conversation += (convoLine + "\n");
	}

	return is;
}
