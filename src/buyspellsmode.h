#ifndef SRC_BUYSPELLSMODE_H_
#define SRC_BUYSPELLSMODE_H_

#include "buyspellchooser.h"
#include "gamemode.h"
#include "town.h"

/* Entered when player chooses to Learn Magic in a town - allows player to pay
 * to learn new spells.
 */
class BuySpellsMode: public GameMode
{
	protected:
		SpellChooser* spellChooser;

		virtual void updateDisplay();
		virtual bool processInput();

		void processTransaction(const SpellTemplate*);

	public:
		BuySpellsMode(const Town&, GameData&, GameState&);
		virtual ~BuySpellsMode();
};

#endif
