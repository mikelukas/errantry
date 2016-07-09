#ifndef SRC_CASTABLESPELL_H_
#define SRC_CASTABLESPELL_H_

#include "effects/effect.h"
#include "spell.h"

class CastableSpell : public Spell
{
	protected:
		Character& caster;
		Character& target;
		vector<Effect*> initializedEffects;

		void clearInitializedEffects();

	public:
		CastableSpell(const Spell*, Character&, Character&);
		virtual ~CastableSpell();

		bool setup();
		void cast();
};

#endif
