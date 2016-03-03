#ifndef _TOWN_H_
#define _TOWN_H_

//Class definition for a town.  Holds all attributes of a town,
//as well as functions for interacting with town features.

#include <string>
#include <istream>
#include <vector>
#include "equipment.h"
#include "point.h"

using std::string;
using std::vector;

using std::istream;

const string TOWN_CONVO_DELIM = "__convo__end";
const char TOWN_SYMBOL = 'T';

class Town
{
	private:
		string name;
		Point location;
		vector<Equipment> weapons;
		vector<Equipment> armor;
		vector<Equipment> items;
		string conversation; //What you hear when you choose to talk in this town

	public:
		string getName();
		Point getLocation();
		vector<Equipment> getShopEquipment(EquipType);
		string getConversation();

		friend istream& operator>> (istream&, Town&);
};

#endif
