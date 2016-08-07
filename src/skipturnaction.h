#ifndef SRC_SKIPTURNACTION_H_
#define SRC_SKIPTURNACTION_H_

#include "battleaction.h"

/* This action does nothing, and should be enqueued for Characters to cause them
 * to lose a turn in battle.
 */
class SkipTurnAction: public BattleAction
{
	protected:
		virtual void doAction() {}
		
	public:
		SkipTurnAction(Character& enqueuer) : BattleAction(enqueuer) {}
		virtual ~SkipTurnAction() {}
};

#endif
