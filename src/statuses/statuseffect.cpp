#include "statuseffect.h"

StatusEffect::StatusEffect(const StatusTemplate& statusTemplate, const EffectParams& effectParams)
	: StatusTemplate(statusTemplate),
	  Effect(effectParams)
{

}

bool StatusEffect::isExpired() const
{
	//postcondition: returns true if this Status's duration has reached 0 turns,
	//false otherwise, or if the Status's duration is unlimited.

	if(durationTurns > 0 || durationTurns == UNLIMITED_DURATION)
	{
		return false;
	}

	return true;
}

void StatusEffect::onTurn()
{
	//postcondition: runTurnEffect() is called to process a subclass-defined
	//action, and durationTurns is decremented if this Status's duration is not
	//unlimited

	if(isExpired())
	{
		return; //probable bug if this is hit; expired Statuses should be removed
	}

	runTurnEffect();

	if(durationTurns != UNLIMITED_DURATION)
	{
		durationTurns--;
	}
}
