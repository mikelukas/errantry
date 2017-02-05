#include <sstream>
#include "../logging/log.h"
#include "../character.h"
#include "mpdamageeffect.h"

MpDamageEffect::MpDamageEffect(const EffectParams& effectParams)
	: Effect(effectParams)
{

}

void MpDamageEffect::runTurnEffect()
{
	//postcondition: target's MP is reduced by BASE_MP_DROP and a message is
	//displayed about how much.

	target.ChangeMP(-1*BASE_MP_DROP);

	std::stringstream mpDmgMsg;
	mpDmgMsg<<target.ShowName()<<" lost "<<BASE_MP_DROP<<" MP!";
	log(mpDmgMsg.str());
}
