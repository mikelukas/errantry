#ifndef SRC_CASTSPELLMODE_H_
#define SRC_CASTSPELLMODE_H_

#include "gamemode.h"
#include "castspellchooser.h"

/* Displays the list of spells the player has in their inventory that can be
 * cast in the field (i.e. outside of battle).
 */
class CastSpellMode: public GameMode
{
	protected:

		Chooser<const SpellTemplate>* spellChooser; //freed in destructor

		int updateDisplay();
		bool processInput(int);

	public:
		CastSpellMode(GameData&, GameState&);
		virtual ~CastSpellMode();
};

#endif
