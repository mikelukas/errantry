#ifndef SRC_BATTLEACTION_H_
#define SRC_BATTLEACTION_H_

/* Abstract base class for queueable actions that can be taken in battle.
 *
 * setup() will be called when the actual is chosen by the player.  This lets the
 * action get more input from the player to prep for executing the action (e.g.
 * choosing a target), while separating this prepwork from the actual execution.
 *
 * execute() will be called if isAborted() is false in battle when the action is
 * ready to run (it will sit in a queue until actions taken ahead of it are
 * executed).
 */
class BattleAction
{
	protected:
		bool aborted;

		void setAborted(bool);

	public:
		BattleAction();
		virtual ~BattleAction() {}

		virtual void setup() {}
		virtual void execute() = 0;

		virtual bool isAborted() { return aborted;}
};

#endif
