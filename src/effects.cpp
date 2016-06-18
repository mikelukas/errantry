#include <iostream>
#include "character.h"
#include "effects.h"

using std::cout;
using std::endl;

void fireDamageFunc(Character& appliedBy, Character& target)
{
	int netDamage = target.applyMagicalDamage(BASE_ELEMENTAL_DAMAGE, fire);


	cout<<appliedBy.ShowName()<<" did "<<netDamage<<" "<<getDisplayNameFor(fire)<<" damage to "<<target.ShowName()<<"!"<<endl;
}

void healFunc(Character& appliedby, Character& target)
{
	target.ChangeHP(25);
}

vector<EffectFunction> initEffects()
{
	vector<EffectFunction> effects;
	effects.push_back(&fireDamageFunc);
	effects.push_back(&healFunc);

	return effects;
}
