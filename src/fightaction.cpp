#include <sstream>
#include "logging/log.h"
#include "fightaction.h"
#include "player.h"

FightAction::FightAction(Character& attacker, Character& defender)
	: BattleAction(attacker),
	  attacker(attacker),
	  defender(defender)
{

}

bool FightAction::isAttackerBlind()
{
	//postcondition: returns true if the taccker has blind status and displays
	//a message that they can't fight.

	if(attacker.hasStatus(BLIND))
	{
		std::stringstream cantSeeMsg;
		cantSeeMsg<<attacker.ShowName()<<" can't see to fight!";
		log(cantSeeMsg.str());
		return true;
	}

	return false;
}

void FightAction::setup()
{
	//postcondition: aborts if attacker is blind.

	if(isAttackerBlind())
	{
		setAborted(true);
	}
}

void FightAction::doAction()
{
	//postcondition:  this function apply's physical damage from the attacker
	//to the defender.  Raw damage from the attacker is based on their AP

	if(isAttackerBlind())
	{
		return;
	}

    int netDamage = defender.applyPhysicalDamage(attacker.getEffectiveAP());

    std::stringstream fightDmgMsg;
    fightDmgMsg<<attacker.ShowName()<<" did "<<netDamage<<" damage to "<<defender.ShowName()<<"!";
    log(fightDmgMsg.str());

    applyWeaponEffects();
}

void FightAction::applyWeaponEffects()
{
	//postcondition: if attacker is a Player, get the player's currently-equipped
	//weapon and apply its affects to the defender.

	Player* attackerAsPlayer = dynamic_cast<Player*>(&attacker); //XXX not a fan of dynamic cast, but eventually equip/dequip functionality may be available at Character levle, and it will be slightly easier to remove this cast and if check, rather than add a whole other subclass just for Player to decorate doAction w/ effect application
	if(attackerAsPlayer != NULL)
	{
		const Equipment* currWeapon = attackerAsPlayer->getCurrentEquipped(WEAPON);
		if(currWeapon == NULL)
		{
			return; //will happen if player hasn't equipped anything
		}

		attackerAsPlayer->applyEquipmentEffects(currWeapon, defender);
	}
}
