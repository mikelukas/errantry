#ifndef SRC_CASTSPELLCHOOSER_H_
#define SRC_CASTSPELLCHOOSER_H_

#include "spellchooser.h"

/* Displays list of spell choices with relevant info for casting */
class CastSpellChooser: public SpellChooser
{
	protected:
		const vector<const SpellTemplate*>* uncastableSpells;

		virtual void displayInventoryChoices() const;
		virtual void displaySpellLine(const SpellTemplate*) const;

	public:
		CastSpellChooser(vector<const SpellTemplate*>*, const Player&);
		CastSpellChooser(vector<const SpellTemplate*>*, vector<const SpellTemplate*>*, const Player&);
		virtual ~CastSpellChooser();
};

#endif
