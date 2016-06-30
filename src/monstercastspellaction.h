#ifndef SRC_MONSTERCASTSPELLACTION_H_
#define SRC_MONSTERCASTSPELLACTION_H_

#include <map>
#include <vector>
#include "castspellaction.h"

using std::map;
using std::vector;

const double HP_PERCENT_TO_PRIORITIZE_HEAL = 0.5f;
const double HP_PERCENT_TO_PRIORITIZE_DEFENSIVE_ASSIST = 0.75f;
const double HP_PERCENT_TO_PRIORITIZE_OFFENSIVE_ASSIST = 0.90f;

/** Allows Monster to choose a spell from its inventory and cast it on a target */
class MonsterCastSpellAction : public CastSpellAction
{
	protected:

		Character* categoryToTarget[NUM_SPELL_CATEGORIES];

		const Spell* lookupSpellIn(const vector<SpellCategory>&) const;
		const Spell* lookupSpellInCategory(SpellCategory) const;

	public:
		MonsterCastSpellAction(Character&, Character&);
		virtual ~MonsterCastSpellAction() {}

		virtual void setup();
};

#endif
