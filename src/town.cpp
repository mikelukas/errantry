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

	string convoLine;
	getline(is,convoLine); //gets the newline character after the location point is read in

	while(getline(is, convoLine) && convoLine != TOWN_CONVO_DELIM) {
		town.conversation += (convoLine + "\n");
	}

	return is;
}
