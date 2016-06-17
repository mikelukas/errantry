#include "character.h"
#include "effects.h"

void fireDamageFunc(Character& appliedBy, Character& target)
{
	target.ChangeHP(-15);
	//Todo: use a magic damage method to apply damage with a weakness
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
