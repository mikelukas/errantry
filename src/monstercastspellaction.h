#ifndef SRC_MONSTERCASTSPELLACTION_H_
#define SRC_MONSTERCASTSPELLACTION_H_

#include <map>
#include "castspellaction.h"
#include "gameData.h"

using std::map;

const double HP_PERCENT_TO_PRIORITIZE_HEAL = 0.5f;

/** Allows Monster to choose a spell from its inventory and cast it on a target */
class MonsterCastSpellAction : public CastSpellAction
{
	protected:
		GameData& gameData;

		const Spell* lookupSpellInCategory(SpellCategory);

	public:
		MonsterCastSpellAction(GameData&, Monster&, Character& enemy);
		virtual ~MonsterCastSpellAction() {}

		virtual void setup();
};

#endif
