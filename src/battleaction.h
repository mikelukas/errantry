#ifndef SRC_BATTLEACTION_H_
#define SRC_BATTLEACTION_H_

#include "Character.h"

/* Abstract base class for queueable actions that can be taken in battle.
 *
 * setup() will be called when the actual is chosen by the player.  This lets the
 * action get more input from the player to prep for executing the action (e.g.
 * choosing a target), while separating this prepwork from the actual execution.
 *
 * isAborted() is checked prior to enqueuing the action.  If returns true, the
 * action won't be enqueued during battle, and thus won't be executed.
 *
 * doAction() should be implemented by subclasses to contain concrete logic
 * for the action when execute() is able to run.
 *
 * execute() calls doAction() if no preconditions that came into play after
 * setup() was called but before execute() was called prevent this action from
 * being run - e.g. target is hit with Stunned status and can't move after they
 * chose an action.
 */
class BattleAction
{
	protected:
		Character& enqueuer;
		bool aborted;

		void setAborted(bool);

		virtual void doAction() = 0;

	public:
		BattleAction(Character& enqueuer);
		virtual ~BattleAction() {}

		virtual void setup() {}
		virtual void execute();

		virtual bool isAborted() { return aborted;}
};

#endif
