#ifndef SRC_CASTSPELLMODE_H_
#define SRC_CASTSPELLMODE_H_

#include "menumode.h"
#include "castspellchooser.h"

/* Displays the list of spells the player has in their inventory that can be
 * cast in the field (i.e. outside of battle).
 */
class CastSpellMode: public MenuMode
{
	protected:

		Chooser<const SpellTemplate>* spellChooser; //freed in destructor

		int displayMenu();
		bool testChoice(int);

	public:
		CastSpellMode(GameData&, GameState&);
		virtual ~CastSpellMode();
};

#endif
