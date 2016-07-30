#ifndef SRC_CASTABLESPELL_H_
#define SRC_CASTABLESPELL_H_

#include "effects/effect.h"
#include "spelltemplate.h"

/* Subclass of SpellTemplate, containing all data needed to setup() and cast()
 * a spell, and holds 1-use state specific to casting a particular spell.
 * A SpellTemplate is required to copy spell metadata for casting, along with the
 * caster and the intended target.
 * setup() should be called first to ensure the spell can be cast, which creates
 * Effects for all the effect ids the spell references and tests if they can be
 * set up.
 * cast() can be called if setup() returns true to run all of the spell's Effects
 * in order. At this time the Effects used are cleared and setup() must be called
 * again to be able to cast the spell.
 */
class CastableSpell : public SpellTemplate
{
	protected:
		Character& caster;
		Character& target;
		vector<Effect*> initializedEffects;

		void deallocInitializedEffects();

	public:
		CastableSpell(const SpellTemplate*, Character&, Character&);
		virtual ~CastableSpell();

		bool setup();
		void cast();
};

#endif
