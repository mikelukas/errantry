#ifndef SRC_CASTABLESPELL_H_
#define SRC_CASTABLESPELL_H_

#include "effects/effect.h"
#include "spelltemplate.h"

class CastableSpell : public SpellTemplate
{
	protected:
		Character& caster;
		Character& target;
		vector<Effect*> initializedEffects;

		void clearInitializedEffects();

	public:
		CastableSpell(const SpellTemplate*, Character&, Character&);
		virtual ~CastableSpell();

		bool setup();
		void cast();
};

#endif
