#include <iostream>
#include "character.h"
#include "effects.h"
#include "meltdownequipmentchooser.h"
#include "randutils.h"

using std::cout;
using std::cin;
using std::endl;

void meltdownFunc(Character& appliedBy, Character& target)
{
	MeltdownEquipmentChooser eqChooser(appliedBy);
	eqChooser.run();

	EquipmentLine meltdownChoice(*(eqChooser.getChoice())); //Copy what they chose so we don't change the quantity of the actual inventory equipment here.

	//Can melt down more than 1 piece of the chosen equipment, so ask player for quantity
	const int available = meltdownChoice.quantity;
	do
	{
		cout<<"How many (up to "<<available<<")? ";
		cin>>meltdownChoice.quantity;
	} while(meltdownChoice.quantity < 1 && meltdownChoice.quantity > available);
}

void monsterMeltdownFunc(Character& appliedBy, Character& target)
{
	vector<EquipmentLine*>* monsterArmament = appliedBy.getWeaponsAndArmorAsVector();
	if(monsterArmament->size() == 0)
	{
		cout<<appliedBy.ShowName()<<" tried to melt down equipment, but doesn't have any!"<<endl;
		delete monsterArmament;
		return;
	}

	//Randomly choose a piece of equipment the monster is carrying
	int eqChoiceIndex = getRandIntBetween(0, monsterArmament->size()-1);
	EquipmentLine* invEqLine = (*monsterArmament)[eqChoiceIndex];

	//Randomly choose a quantity of that equipment to meltdown
	int meltdownQuantity = getRandIntBetween(1, invEqLine->quantity);
	EquipmentLine meltdownEqLine(invEqLine->pEquipment, meltdownQuantity); //new eqline so changing quantity here doesn't affect original eqline in inventory

	//Do the actual meltdown
	meltdownEquipment(appliedBy, target, meltdownEqLine);

	delete monsterArmament;
}

void meltdownEquipment(Character& appliedBy, Character& target, EquipmentLine& meltdownChoice)
{
	//Remove chosen quantity of chosen equipment
	appliedBy.RemoveEquipment(&meltdownChoice);

	//Convert equipment stats to damage and deal it to the target
	int rawMeltdownDamage = meltdownChoice.quantity * (meltdownChoice.pEquipment->getStatMod().getMeltdownDamage());
	int netDamage = target.applyMagicalDamage(rawMeltdownDamage, fire);

	cout<<appliedBy.ShowName()<<" melted down "<<meltdownChoice.quantity<<" "<<meltdownChoice.pEquipment->getName()<<" into "<<netDamage<<" "<<getDisplayNameFor(fire)<<" damage to "<<target.ShowName()<<"!"<<endl;
}

vector<EffectFunction> initEffects()
{
	vector<EffectFunction> effects;
	effects.push_back(&meltdownFunc);

	//monster-only effect functions
	effects.push_back(&monsterMeltdownFunc);

	return effects;
}
