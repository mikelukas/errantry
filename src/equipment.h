#ifndef _EQUIPMENT_H_
#define _EQUIPMENT_H_

#include <string>

using std::string;

enum type {weapon, armor, item};

struct EquipType
    {
        int statUp;     //how much additional AP/DP/HP/MP given by item
        int cost;   //price the item sells for
        int quantity;
        type type;
        string name;
    };

#endif
