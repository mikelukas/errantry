#include <sstream>
#include "../logging/log.h"
#include "../character.h"
#include "monstermeltdowneffect.h"
#include "../util/randutils.h"

MonsterMeltdownEffect::MonsterMeltdownEffect(const EffectParams& effectParams)
	: MeltdownEffect(effectParams)
{

}

EquipmentLine* MonsterMeltdownEffect::chooseEquipment() const
{
	//postcondition: chooses a random piece of equipment, and a random quantity
	//of that equipment, from the monster's inventory, allocates a new EquipmentLine
	//for it, and returns it.  Will return NULL if monster has no equipment.

	vector<EquipmentLine*>* monsterArmament = applier.getWeaponsAndArmorAsVector();
	if(monsterArmament->size() == 0)
	{
		std::stringstream meltedStr;
		meltedStr<<applier.ShowName()<<" tried to melt down equipment, but doesn't have any!";
		log(meltedStr.str());

		delete monsterArmament;
		return NULL;
	}

	//Randomly choose a piece of equipment the monster is carrying
	int eqChoiceIndex = getRandIntBetween(0, monsterArmament->size()-1);
	EquipmentLine* invEqLine = (*monsterArmament)[eqChoiceIndex];
	delete monsterArmament;

	//Randomly choose a quantity of that equipment to meltdown
	int meltdownQuantity = getRandIntBetween(1, invEqLine->quantity);
	return new EquipmentLine(invEqLine->pEquipment, meltdownQuantity); //new eqline so changing quantity here doesn't affect original eqline in inventory
}
