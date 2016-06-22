#include <iostream>
#include "character.h"
#include "effects.h"

using std::cout;
using std::cin;
using std::endl;

void elementalDamage(Character& appliedBy, Character& target, int rawDamage, Element element)
{
	int netDamage = target.applyMagicalDamage(rawDamage, element);

	cout<<appliedBy.ShowName()<<" did "<<netDamage<<" "<<getDisplayNameFor(element)<<" damage to "<<target.ShowName()<<"!"<<endl;
}

void fireDamageFunc(Character& appliedBy, Character& target)
{
	elementalDamage(appliedBy, target, BASE_ELEMENTAL_DAMAGE, fire);
}

void waterDamageFunc(Character& appliedBy, Character& target)
{
	elementalDamage(appliedBy, target, BASE_ELEMENTAL_DAMAGE, water);
}

void airDamageFunc(Character& appliedBy, Character& target)
{
	elementalDamage(appliedBy, target, BASE_ELEMENTAL_DAMAGE, air);
}

void earthDamageFunc(Character& appliedBy, Character& target)
{
	elementalDamage(appliedBy, target, BASE_ELEMENTAL_DAMAGE, earth);
}

void nonElementalMagicDamageFunc(Character& appliedBy, Character& target)
{
	elementalDamage(appliedBy, target, BASE_ELEMENTAL_DAMAGE, none);
}

void healFunc(Character& appliedby, Character& target)
{
	target.ChangeHP(25);
}

void fearFunc(Character& appliedby, Character& target)
{
	//postcondition: caster is prompted to choose an Element, and target is made
	//weak to that element.

	int elementChoiceNum = none;
	cout<<"Choose a weakness to add to "<<target.ShowName()<<": "<<endl;
	do
	{
		for(int i=0; i < ELEMENTS.size()-1; i++)
		{
			cout<<i+1<<") "<<getDisplayNameFor(ELEMENTS[i])<<endl;
		}
		cin>>elementChoiceNum;
	} while(elementChoiceNum < 1 || elementChoiceNum-1 > ELEMENTS.size()-1);

	Element elementChoice = static_cast<Element>(elementChoiceNum-1);
	target.addWeakness(elementChoice);

	cout<<target.ShowName()<<" is now weak to "<<getDisplayNameFor(elementChoice)<<"."<<endl;
}

void enervateFunc(Character& appliedBy, Character& target)
{
	target.ChangeMP(-1*BASE_MP_DROP);

	cout<<target.ShowName()<<" lost "<<BASE_MP_DROP<<" MP!"<<endl;
}

vector<EffectFunction> initEffects()
{
	vector<EffectFunction> effects;
	effects.push_back(&fireDamageFunc);
	effects.push_back(&waterDamageFunc);
	effects.push_back(&airDamageFunc);
	effects.push_back(&earthDamageFunc);
	effects.push_back(&nonElementalMagicDamageFunc);
	effects.push_back(&healFunc);
	effects.push_back(&fearFunc);
	effects.push_back(&enervateFunc);

	return effects;
}
