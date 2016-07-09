#ifndef SRC_SPELLCHOOSER_H_
#define SRC_SPELLCHOOSER_H_

#include <iostream>
#include "inventorychooser.h"
#include "player.h"
#include "spelltemplate.h"
#include "statsdisplayer.h"

using std::cout;
using std::endl;

/* Lists spells in player's inventorye*/
class SpellChooser: public InventoryChooser<const SpellTemplate>
{
	protected:
		const Player& player;

		virtual void displayRelevantStats() const;
		virtual void displayInventoryChoices() const;

		virtual void displayChoice(int, const SpellTemplate*) const;
		virtual void displaySpellLine(const SpellTemplate*) const = 0;

	public:
		SpellChooser(vector<const SpellTemplate*>*, const Player&);
		virtual ~SpellChooser() {}
};

#endif
