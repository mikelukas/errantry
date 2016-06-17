#ifndef SRC_MONSTERCASTSPELLACTION_H_
#define SRC_MONSTERCASTSPELLACTION_H_

#include <map>
#include "castspellaction.h"

using std::map;

const double HP_PERCENT_TO_PRIORITIZE_HEAL = 0.5f;

/** Allows Monster to choose a spell from its inventory and cast it on a target */
class MonsterCastSpellAction : public CastSpellAction
{
	protected:

		const Spell* lookupSpellInCategory(SpellCategory);

	public:
		MonsterCastSpellAction(Character&, Character&);
		virtual ~MonsterCastSpellAction() {}

		virtual void setup();
};

#endif
