#ifndef SRC_USEITEMACTION_H_
#define SRC_USEITEMACTION_H_

#include "battleaction.h"
#include "battleusableitemchooser.h"
#include "equipment.h"
#include "player.h"

/* BattleAction for selecting an item and target on which to use it in battle */
class UseItemAction : public BattleAction
{
	protected:
		Player& player;
		Monster& monster;

		const Equipment* pEquipmentChoice;
		Character* pTarget;

		void setTarget(Character&);

	public:
		UseItemAction(Player& player, Monster& monster);
		virtual ~UseItemAction() {}

		virtual void setup();
		virtual void execute();
};

#endif
