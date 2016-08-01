#ifndef _EQUIPMENT_H_
#define _EQUIPMENT_H_

#include <iostream>
#include <algorithm> //min
#include <math.h> //round
#include <string>
#include <vector>

using std::istream;
using std::ostream;

using std::min;
using std::string;
using std::vector;

enum EquipType {WEAPON, ARMOR, ITEM};

const float USED_EQUIPMENT_MARKDOWN = 0.5f; //% of original cost player gets when selling equipment
const int INF_QUANTITY = -1; //For shops that sell equipment, you can buy as much as you can afford, and equipment lines need SOME kind of quantity, so this is a sentinel value for infinity

//Encapsulates changes to stats caused by using a piece of equipment
struct StatMod
	{
		int hpMod;
		int mpMod;
		int apMod;
		int dpMod;
		int mdpMod;
		int spMod;

		StatMod();

		int getMeltdownDamage() const;

		friend istream& operator>> (istream&, StatMod&);
		friend ostream& operator<< (ostream&, const StatMod&);

		friend void operator+=(StatMod&, const StatMod&);
		friend void operator-=(StatMod&, const StatMod&);
	};
const StatMod NO_STATMOD;

class Equipment
    {
		private:
			EquipType type;
			string name;

			StatMod statMods;
			int cost;   //price the item sells for

		public:
			Equipment(EquipType type);

			string getName() const;
			EquipType getType() const;
			int getCost() const;
			int getSellPrice() const;
			const StatMod& getStatMod() const;

			friend istream& operator>> (istream&, Equipment&);
    };

struct EquipmentLine
	{
		const Equipment* pEquipment;
		int quantity;

		EquipmentLine(); //Constructs a NULL object essentially; pEquipment is null and quantity is 0
		EquipmentLine(const Equipment*);
		EquipmentLine(const Equipment*, const int);

		int getTotalCost() const;
		int getTotalSellPrice() const;

		friend void operator+=(EquipmentLine&, const EquipmentLine&);
		friend void operator-=(EquipmentLine&, const EquipmentLine&);
	};

#endif
