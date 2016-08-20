#ifndef SRC_FIGHTACTION_H_
#define SRC_FIGHTACTION_H_

#include "battleaction.h"
#include "character.h"

/* Battle action for handling attacker's choice to do physical damage to defender.*/
class FightAction : public BattleAction
{
	protected:

		Character& attacker;
		Character& defender;

		virtual void doAction();
		virtual bool isAttackerBlind();
		virtual void applyWeaponEffects();

	public:
		FightAction(Character&, Character&);
		virtual ~FightAction() {}

		virtual void setup();
};

#endif
