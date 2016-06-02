#ifndef SRC_SPELLCHOOSER_H_
#define SRC_SPELLCHOOSER_H_

#include <iostream>
#include "inventorychooser.h"
#include "player.h"
#include "spell.h"
#include "statsdisplayer.h"

using std::cout;
using std::endl;

/* Lists spells in player's inventorye*/
class SpellChooser: public InventoryChooser<const Spell>
{
	protected:
		const Player& player;

		virtual void displayRelevantStats() const;
		virtual void displayInventoryChoices() const;

		virtual void displaySpellLine(const Spell*) const = 0;

	public:
		SpellChooser(vector<const Spell*>*, const Player&);
		virtual ~SpellChooser() {}
};

#endif
