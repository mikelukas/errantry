#ifndef _MONSTER_H
#define _MONSTER_H

//Mike Lukas -p2prog03-             - monster.h -
//Class definition for a monster.  This class holds all the attributes
//and operations a monster will need, such as HP changing and accessing
//various attributes of the monster from in the program

#include <istream>
#include <string>
#include <vector>
#include "character.h"
#include "equipment.h"
#include "streamutils.h"

using std::istream;
using std::string;
using std::vector;

class Monster : public Character
    {
		protected:

			//equipment player may get at end of combat
			vector<int> weaponIds;
			vector<int> armorIds;
			vector<int> itemIds;

        public:
            Monster();

            vector<int> getEquipmentIds(EquipType) const;
            void apply(const Equipment*);

            friend istream& operator>> (istream&, Monster&);
    };

#endif
