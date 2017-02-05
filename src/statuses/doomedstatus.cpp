#include <sstream>
#include "../logging/log.h"
#include "../character.h"
#include "doomedstatus.h"

DoomedStatus::DoomedStatus(const StatusTemplate& statusTemplate, const EffectParams& params)
	: StatusEffect(statusTemplate, params)
{

}

void DoomedStatus::onAdd()
{
	std::stringstream doomed;
	doomed<<target.ShowName()<<" is doomed!";
	log(doomed.str());
}

void DoomedStatus::onRemove()
{
	//postcondition: if this status's duration hit 0, the target's HP is brought
	//to 0, otherwise, if it was removed prior to hitting 0 a message is displayed
	//stating that the target will not die.

	std::stringstream removeMsg;
	if(isExpired())
	{
		removeMsg<<target.ShowName()<<" succumbs to Doom!";
		target.ChangeHP(-(target.getEffectiveMaxHP()));
	}
	else
	{
		removeMsg<<target.ShowName()<<" is saved from certain death!";
	}

	log(removeMsg.str());
}

const string DoomedStatus::getName() const
{
	//postcondition: return's this status's name plus its remaining duration,
	//so it is clear how many turns the target has to live.

	std::stringstream doomSS;
	doomSS<<StatusEffect::getName()<<" "<<durationTurns;

	return doomSS.str();
}
