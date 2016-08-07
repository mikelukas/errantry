#include "battleaction.h"

BattleAction::BattleAction(Character& enqueuer)
	: enqueuer(enqueuer),
	  aborted(false)
{

}

void BattleAction::setAborted(bool aborted)
{
	this->aborted = aborted;
}

void BattleAction::execute()
{
	//postcondition: runs this action's logic in doAction() if the enqueuer is
	//not stunned.  If they are, nothing happens.

	if(enqueuer.hasStatus(STUNNED))
	{
		return;
	}

	doAction();
}
