#ifndef SRC_CASTSPELLACTION_H_
#define SRC_CASTSPELLACTION_H_

#include <iostream>

#include "battleaction.h"
#include "spell.h"

using std::cout;
using std::endl;

/* Intended to be used as the base for both player and monster spell casting
 * in battle.*/
class CastSpellAction: public BattleAction
{
	protected:

		Character& caster;
		Character& enemy;  //target option for the spell caster.  Character b/c a monster could cast a spell on the player

		const Spell* spellChoice;
		Character* spellTarget;

	public:
		CastSpellAction(Character&, Character&);
		virtual ~CastSpellAction() {}

		virtual void execute();
};

#endif
