#ifndef SRC_PURCHASEPELLCHOOSER_H_
#define SRC_PURCHASEPELLCHOOSER_H_

#include "spellchooser.h"

/* SpellChooser for places that sell spells - displays list of Spells with purchase prices */
class BuySpellChooser: public SpellChooser
{
	protected:
		virtual void displayInventoryChoices() const;
		virtual void displaySpellLine(const Spell*) const;

		virtual void displayPostChoiceListInfo() const;

	public:
		BuySpellChooser(vector<const Spell*>*, const Player&);
		virtual ~BuySpellChooser() {}
};

#endif
