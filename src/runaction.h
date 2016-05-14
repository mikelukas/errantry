#ifndef SRC_RUNACTION_H_
#define SRC_RUNACTION_H_

#include "battleaction.h"
#include "gamestate.h"

/* Battle action for running from battle (exits current mode)*/
class RunAction : public BattleAction
{
	protected:

		GameState& gameState;

		void execute();

	public:
		RunAction(GameState&);
		virtual ~RunAction() {}
};

#endif
