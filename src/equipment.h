#ifndef _EQUIPMENT_H_
#define _EQUIPMENT_H_

#include <iostream>
#include <string>

using std::istream;
using std::ostream;

using std::string;

enum EquipType {WEAPON, ARMOR, ITEM};

//Encapsulates changes to stats caused by using a piece of equipment
struct StatMod
	{
		int hpMod;
		int apMod;
		int dpMod;
		int spMod;

		friend istream& operator>> (istream&, StatMod&);
		friend ostream& operator<< (ostream&, const StatMod&);
	};

class Equipment
    {
		private:
			EquipType type;
			string name;

			StatMod statMods;
			int cost;   //price the item sells for
			int quantity;

		public:
			Equipment(EquipType type);

			string getName();
			EquipType getType();
			int getCost();
			StatMod& getStatMod();

			friend istream& operator>> (istream&, Equipment&);
    };

#endif
