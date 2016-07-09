#ifndef SRC_PURCHASEPELLCHOOSER_H_
#define SRC_PURCHASEPELLCHOOSER_H_

#include "spellchooser.h"

/* SpellChooser for places that sell spells - displays list of Spells with purchase prices */
class BuySpellChooser: public SpellChooser
{
	protected:
		virtual void displayInventoryChoices() const;
		virtual void displaySpellLine(const SpellTemplate*) const;

		virtual void displayPostChoiceListInfo() const;

		virtual bool validate() const;

	public:
		BuySpellChooser(vector<const SpellTemplate*>*, const Player&);
		virtual ~BuySpellChooser() {}
};

#endif
