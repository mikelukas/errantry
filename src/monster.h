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
#include "util/streamutils.h"

class BattleStrategy; //Forward declaration since BattleStragry and Monster are interdependent

using std::istream;
using std::string;
using std::vector;

class Monster : public Character
    {
		protected:

			//determines what actions the monster takes in battle
			BattleStrategy* battleStrategy;

			set<const SpellTemplate*> droppableSpells; //spells monster won't cast but can drop when defeateda

        public:
            Monster(string&, int, int, int, int, int, int, int, int);
            Monster(const Monster&);
            ~Monster();

            BattleStrategy* getBattleStrategy() const;
            const set<const SpellTemplate*>& getDroppableSpells() const;

            void AddDroppableSpell(const SpellTemplate*);
    };

#endif
