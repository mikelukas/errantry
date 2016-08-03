#include <iostream>
#include "../character.h"
#include "curestatuseffect.h"

using std::cout;
using std::endl;

CureStatusEffect::CureStatusEffect(EffectType typeToCure, const EffectParams& effectParams)
	: Effect(effectParams),
	  typeToCure(typeToCure)
{

}

void CureStatusEffect::runTurnEffect()
{
	//postcondition: if the target has the status held in typeToCure, it is removed.
	target.removeStatus(typeToCure);
}
