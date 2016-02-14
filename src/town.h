#ifndef _TOWN_H_
#define _TOWN_H_

#include <string>
#include <istream>
#include "point.h"

using std::string;

using std::istream;

const string TOWN_CONVO_DELIM = "__convo__end";
const char TOWN_SYMBOL = 'T';

class Town
{
	private:
		string name;
		Point location;
		string conversation; //What you hear when you choose to talk in this town

	public:
		string getName();
		Point getLocation();
		string getConversation();

		friend istream& operator>> (istream&, Town&);
};

#endif
