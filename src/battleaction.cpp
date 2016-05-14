#include "battleaction.h"

BattleAction::BattleAction()
	: aborted(false)
{

}

void BattleAction::setAborted(bool aborted)
{
	this->aborted = aborted;
}
