#ifndef SRC_BATTLEUSABLEITEMCHOOSER_H_
#define SRC_BATTLEUSABLEITEMCHOOSER_H_

#include "statsdisplayer.h"
#include "usableitemchooser.h"

/* Used for choosing Items in player's inventory during battle for use on either
 * the player or monster.
 * Displays stats for both the player and monster, slightly more abbreviated than
 * when choosing from the overworld, and lists only Items from player inventory.
 */
class BattleUsableItemChooser : public UsableItemChooser
{
	protected:
		const Monster& monster;

		virtual void displayRelevantStats() const;

	public:
		BattleUsableItemChooser(Player&, const Monster&);
		virtual ~BattleUsableItemChooser() {};
};

#endif
