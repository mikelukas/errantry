#ifndef _TOWN_H_
#define _TOWN_H_

//Class definition for a town.  Holds all attributes of a town,
//as well as functions for interacting with town features.

#include <istream>
#include <string>
#include <vector>
#include "equipment.h"
#include "point.h"

using std::istream;
using std::string;
using std::vector;

const string TOWN_CONVO_DELIM = "__convo__end";
const char TOWN_SYMBOL = 'T';

class Town
{
	private:
		string name;
		Point location;
		vector<int> weaponIds;
		vector<int> armorIds;
		vector<int> itemIds;
		string conversation; //What you hear when you choose to talk in this town

	public:
		string getName() const;
		Point getLocation() const;
		vector<int> getShopEquipmentIds(EquipType) const;
		string getConversation() const;

		friend istream& operator>> (istream&, Town&);
};

#endif
