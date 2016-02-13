#include "town.h"

string Town::getName()
{
	return name;
}

string Town::getConversation()
{
	return conversation;
}

int Town::locationAsIndex(int mapWidth)
{
	return location.y*mapWidth + location.x;
}

istream& operator>> (istream& is, Town& town)
{
	is>>town.name;
	is>>town.location;

	string convoLine;
	getline(is,convoLine); //gets the newline character after the location point is read in

	while(getline(is, convoLine) && convoLine != TOWN_CONVO_DELIM) {
		town.conversation += (convoLine + "\n");
	}

	return is;
}
