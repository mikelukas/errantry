#include "../character.h"
#include "monsterremoveweaknesseffect.h"

#include "../util/randutils.h"

MonsterRemoveWeaknessEffect::MonsterRemoveWeaknessEffect(const EffectParams& effectParams)
	: RemoveWeaknessEffect(effectParams)
{

}

Element MonsterRemoveWeaknessEffect::chooseWeakness()
{
	//postcondition: one of the monster's weakness is removed, or the effect
	//is aborted if the monster isn't weak to anything.

	//Get target's current weaknesses, so we can remove only weaknesses that they actually have
	const set<Element>& targetWeaknesses = target.getWeaknesses();
	if(targetWeaknesses.empty())
	{
		cout<<target.ShowName()<<" is not weak to anything."<<endl;
		return none;
	}

	//Iterate (can't randomly access sets) to the index of the weakness we want to remove in the set
	int weaknessToSeek = getRandIntBetween(0, targetWeaknesses.size()-1); //-1 b/c range is inclusive
	set<Element>::const_iterator it = targetWeaknesses.begin();
	for(int i=0; i < weaknessToSeek && it != targetWeaknesses.end(); i++)
	{
		it++;//advance iterator to position of the weakness we want to remove;
	}

	return (*it);
}
