#include <iostream>
#include "character.h"
#include "effects.h"
#include "elementchooser.h"
#include "meltdownequipmentchooser.h"
#include "randutils.h"

using std::cout;
using std::cin;
using std::endl;

void healFunc(Character& appliedby, Character& target)
{
	target.ChangeHP(25);
}

void fearFunc(Character& appliedby, Character& target)
{
	//postcondition: caster is prompted to choose an Element, and target is made
	//weak to that element.

	cout<<"Choose a weakness to add to "<<target.ShowName()<<":"<<endl;
	ElementChooser elementChooser;
	elementChooser.run();

	const Element* elementChoice = elementChooser.getChoice();
	applyWeaknessTo(target, *elementChoice);
}

void monsterFearFunc(Character& appliedBy, Character& target)
{
	//postcondition: target is made weak to an element to which they are not already
	//weak, prioritizing elements of spells that applied by has the most of.  E.g.
	//if applied by has 5 fire spells, and 4 water spells, target will be made
	//weak to fire if they are not already weak to it, otherwise they will be made
	//weak to water.
	//If target is already weak toward all elements in spells that appliedBy has,
	//then target is made weak to first Element they are not already weak to, or
	//nothing if they are weak to everything.

	set<SpellCategory> offensiveSpellCategories;
	offensiveSpellCategories.insert(ATTACK);

	const set<pair<Element, int>, bool(*)(const pair<Element, int>&, const pair<Element, int>&)>* elementsByCount = appliedBy.getSpellElementCounts(offensiveSpellCategories);
	for(set<pair<Element, int>, bool(*)(const pair<Element, int>&, const pair<Element, int>&)>::const_reverse_iterator it = elementsByCount->rbegin(); it != elementsByCount->rend(); it++)
	{
		Element el = it->first;
		if(!target.isWeakAgainst(el))
		{
			applyWeaknessTo(target, el);
			break;
		}
	}
	delete elementsByCount;
}

void applyWeaknessTo(Character& target, Element elementChoice)
{
	target.addWeakness(elementChoice);

	cout<<target.ShowName()<<" is now weak to "<<getDisplayNameFor(elementChoice)<<"."<<endl;
}

void courageFunc(Character& appliedBy, Character& target)
{
	//postcondition: caster is prompted to choose an Element, and target loses
	//weakness to that element (if any)

	cout<<"Choose a weakness to remove from "<<target.ShowName()<<":"<<endl;
	ElementChooser elementChooser;
	elementChooser.run();

	const Element* elementChoice = elementChooser.getChoice();

	target.removeWeakness(*elementChoice);

	cout<<target.ShowName()<<" no longer is weak to "<<getDisplayNameFor(*elementChoice)<<"."<<endl;
}

void monsterCourageFunc(Character& appliedBy, Character& target)
{
	//Get target's current weaknesses, so we can remove only weaknesses that they actually have
	const set<Element>& targetWeaknesses = target.getWeaknesses();
	if(targetWeaknesses.empty())
	{
		cout<<target.ShowName()<<" is not weak to anything."<<endl;
		return;
	}

	//Iterate (can't randomly access sets) to the index of the weakness we want to remove in the set
	int weaknessToSeek = getRandIntBetween(0, targetWeaknesses.size()-1); //-1 b/c range is inclusive
	set<Element>::const_iterator it = targetWeaknesses.begin();
	for(int i=0; i < weaknessToSeek && it != targetWeaknesses.end(); i++)
	{
		it++;//advance iterator to position of the weakness we want to remove;
	}

	removeWeaknessFrom(target, (*it));
}

void removeWeaknessFrom(Character& target, Element elementChoice)
{
	target.removeWeakness(elementChoice);

	cout<<target.ShowName()<<" no longer is weak to "<<getDisplayNameFor(elementChoice)<<"."<<endl;
}

void enervateFunc(Character& appliedBy, Character& target)
{
	target.ChangeMP(-1*BASE_MP_DROP);

	cout<<target.ShowName()<<" lost "<<BASE_MP_DROP<<" MP!"<<endl;
}

void drainFunc(Character& appliedBy, Character& target)
{
	int netDamage = target.applyMagicalDamage(BASE_DRAIN_HP, water);
	appliedBy.ChangeHP(netDamage); //add to applier's HP amount done in magical damage

	cout<<appliedBy.ShowName()<<" drained "<<netDamage<<" HP from "<<target.ShowName()<<"!"<<endl;
}

void channelFunc(Character& appliedBy, Character& target)
{
	int baseChannelDamage;
	cout<<"Enter amount of your HP to convert into Fire damage (up to "<<appliedBy.Health()-1<<"): ";
	do
	{
		cin>>baseChannelDamage;
	}while(!validateChannelDamage(appliedBy, baseChannelDamage));

	appliedBy.ChangeHP(-1*baseChannelDamage);
	int netDamage = target.applyMagicalDamage(baseChannelDamage, fire);
	cout<<appliedBy.ShowName()<<" channeled "<<baseChannelDamage<<" HP into "<<netDamage<<" "<<getDisplayNameFor(fire)<<" damage to "<<target.ShowName()<<"!"<<endl;
}

bool validateChannelDamage(Character& appliedBy, int inputDamage)
{
	if(inputDamage < 0)
	{
		cout<<"Can't channel a negative amount of HP!"<<endl;
		return false;
	}

	if(inputDamage >= appliedBy.Health())
	{
		cout<<"Channeling all of your HP would kill you!"<<endl;
		return false;
	}

	return true;
}

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
	effects.push_back(&healFunc);
	effects.push_back(&fearFunc);
	effects.push_back(&courageFunc);
	effects.push_back(&enervateFunc);
	effects.push_back(&drainFunc);
	effects.push_back(&channelFunc);
	effects.push_back(&meltdownFunc);

	//monster-only effect functions
	effects.push_back(&monsterFearFunc);
	effects.push_back(&monsterCourageFunc);
	effects.push_back(&monsterMeltdownFunc);

	return effects;
}
