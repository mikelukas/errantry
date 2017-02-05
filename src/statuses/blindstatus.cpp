#include <sstream>
#include "../logging/log.h"
#include "blindstatus.h"
#include "../character.h"

BlindStatus::BlindStatus(const StatusTemplate& statusTemplate, const EffectParams& params)
	: StatusEffect(statusTemplate, params)
{

}

void BlindStatus::onAdd()
{
	std::stringstream blinded;
	blinded<<target.ShowName()<<" can't see!";
	log(blinded.str());
}

void BlindStatus::onRemove()
{
	std::stringstream unblinded;
	unblinded<<target.ShowName()<<" can see again.";
	log(unblinded.str());
}
