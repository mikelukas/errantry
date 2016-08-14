#include <iostream>
#include "../character.h"
#include "curestatuseseffect.h"

using std::cout;
using std::endl;

CureStatusesEffect::CureStatusesEffect(EffectType typeToCure, const EffectParams& effectParams)
	: Effect(effectParams),
	  typeToCure(typeToCure)
{

}

void CureStatusesEffect::runTurnEffect()
{
	//postcondition: if the target has the status held in typeToCure, it is removed.
	target.removeStatus(typeToCure);
}
