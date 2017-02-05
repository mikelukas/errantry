#include <sstream>
#include "../logging/log.h"
#include "../character.h"
#include "mutestatus.h"

MuteStatus::MuteStatus(const StatusTemplate& statusTemplate, const EffectParams& params)
	: StatusEffect(statusTemplate, params)
{

}

void MuteStatus::onAdd()
{
	std::stringstream addMsg;
	addMsg<<target.ShowName()<<" is unable to speak!";
	log(addMsg.str());
}

void MuteStatus::onRemove()
{
	std::stringstream removedMsg;
	removedMsg<<target.ShowName()<<" can speak again.";
	log(removedMsg.str());
}
