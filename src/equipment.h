#ifndef _EQUIPMENT_H_
#define _EQUIPMENT_H_

#include <iostream>
#include <algorithm> //min
#include <math.h> //round
#include <set>
#include <string>
#include <vector>
#include "element.h"
#include "statmod.h"

using std::istream;
using std::ostream;

using std::min;
using std::set;
using std::string;
using std::vector;

enum EquipType {WEAPON, ARMOR, ITEM};

const float USED_EQUIPMENT_MARKDOWN = 0.5f; //% of original cost player gets when selling equipment
const int INF_QUANTITY = -1; //For shops that sell equipment, you can buy as much as you can afford, and equipment lines need SOME kind of quantity, so this is a sentinel value for infinity

class Equipment
    {
		private:
			EquipType type;
			string name;
			Element element;

			StatMod statMods;
			set<int> effectImmunityIds;
			vector<int> effectIds;

			int cost;   //price the item sells for

		public:
			Equipment(EquipType type);

			string getName() const;
			EquipType getType() const;
			Element getElement() const;
			int getCost() const;
			int getSellPrice() const;
			const StatMod& getStatMod() const;
			const set<int>& getEffectImmunityIds() const;
			const vector<int>& getEffectIds() const;

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
