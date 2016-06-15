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

class BattleStrategy; //Forward declaration since BattleStragry and Monster are interdependent

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

			//spells player may learn by defeating the monster
			vector<int> spellIds;

			//determines what actions the monster takes in battle
			BattleStrategy* battleStrategy;

        public:
            Monster();
            Monster(const Monster&);
            ~Monster();

            vector<int> getEquipmentIds(EquipType) const;
            vector<int> getSpellIds() const;

            BattleStrategy* getBattleStrategy() const;

            void apply(const Equipment*);

            friend istream& operator>> (istream&, Monster&);
    };

#endif
