#ifndef SRC_PLAYERCASTSPELLACTION_H_
#define SRC_PLAYERCASTSPELLACTION_H_

#include "castspellaction.h"
#include "castspellchooser.h"
#include "targetchooser.h"

/* BattleAction allowing player to choose a spell to cast on eligible targets
 * in battle.  Will display target choices if there is more than one option.
 */
class PlayerCastSpellAction : public CastSpellAction
{
	protected:

		CastSpellChooser spellChooser;

		virtual bool setupSpellChoice();
		virtual bool setupTargetChoice();

	public:
		PlayerCastSpellAction(Player&, Monster&);
		virtual ~PlayerCastSpellAction() {}


};

#endif
