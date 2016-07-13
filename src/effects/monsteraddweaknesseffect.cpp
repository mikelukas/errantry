#include <set>
#include "../character.h"
#include "monsteraddweaknesseffect.h"

using std::set;

MonsterAddWeaknessEffect::MonsterAddWeaknessEffect(const EffectParams& effectParams)
	: AddWeaknessEffect(effectParams)
{

}

Element MonsterAddWeaknessEffect::chooseWeakness()
{
	//postcondition: target is made weak to an element to which they are not already
	//weak, prioritizing elements of spells that applier has the most of.  E.g.
	//if applier has 5 fire spells, and 4 water spells, target will be made
	//weak to fire if they are not already weak to it, otherwise they will be made
	//weak to water.
	//If target is already weak toward all elements in spells that applier has,
	//then target is made weak to first Element they are not already weak to, or
	//nothing if they are weak to everything.

	set<SpellCategory> offensiveSpellCategories;
	offensiveSpellCategories.insert(ATTACK);

	Element weaknessChoice = none;
	const set<pair<Element, int>, bool(*)(const pair<Element, int>&, const pair<Element, int>&)>* elementsByCount = applier.getSpellElementCounts(offensiveSpellCategories);
	for(set<pair<Element, int>, bool(*)(const pair<Element, int>&, const pair<Element, int>&)>::const_reverse_iterator it = elementsByCount->rbegin(); it != elementsByCount->rend(); it++)
	{
		Element el = it->first;
		if(!target.isWeakAgainst(el))
		{
			weaknessChoice = el;
			break;
		}
	}

	delete elementsByCount;
	return weaknessChoice;
}
