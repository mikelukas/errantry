#ifndef _MONSTER_H
#define _MONSTER_H

//Mike Lukas -p2prog03-             - monster.h -
//Class definition for a monster.  This class holds all the attributes
//and operations a monster will need, such as HP changing and accessing
//various attributes of the monster from in the program

#include <string>
#include "character.h"

using std::string;

class Monster : public Character
    {
        public:
            Monster();
            void SetAttributes(int, int, int, int, int, int, string&);

            void apply(const Equipment*);
    };

#endif
