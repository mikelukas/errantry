#include "effects.h"

void fireDamageFunc(Character& appliedBy, Character& target)
{
	target.ChangeHP(-15);
	//Todo: use a magic damage method to apply damage with a weakness
}

vector<EffectFunction> initEffects()
{
	vector<EffectFunction> effects;
	effects.push_back(&fireDamageFunc);

	return effects;
}
