#include <iostream>
#include "character.h"
#include "effects.h"

using std::cout;
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

vector<EffectFunction> initEffects()
{
	vector<EffectFunction> effects;
	effects.push_back(&fireDamageFunc);
	effects.push_back(&waterDamageFunc);
	effects.push_back(&airDamageFunc);
	effects.push_back(&earthDamageFunc);
	effects.push_back(&nonElementalMagicDamageFunc);
	effects.push_back(&healFunc);

	return effects;
}
