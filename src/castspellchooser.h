#ifndef SRC_CASTSPELLCHOOSER_H_
#define SRC_CASTSPELLCHOOSER_H_

#include "spellchooser.h"

/* Displays list of spell choices with relevant info for casting */
class CastSpellChooser: public SpellChooser
{
	protected:
		const vector<const Spell*>* uncastableSpells;

		virtual void displayInventoryChoices() const;
		virtual void displaySpellLine(const Spell*) const;

	public:
		CastSpellChooser(vector<const Spell*>*, const Player&);
		CastSpellChooser(vector<const Spell*>*, vector<const Spell*>*, const Player&);
		virtual ~CastSpellChooser();
};

#endif
