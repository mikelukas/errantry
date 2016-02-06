#ifndef _SPELL_H
#define _SPELL_H

//Mike Lukas -p2prog03 - spell.h-
//This file just holds the two data types, SpellType and elemType for
//use in each class.
#include <string>

using std::string;

enum elemType {fire, air, earth, water, none};

struct SpellType
    {
        int MAP;            //attack power of spell
        int cost;           //cost in MP
        string name;      //name of spell
        elemType element;   //basic elemental type of spell
    };
    
#endif
