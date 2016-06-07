#include "playercastspellaction.h"

PlayerCastSpellAction::PlayerCastSpellAction(Player& player, Monster& monster)
	: CastSpellAction(player, monster),
	  spellChooser(player.getSpellsForLocale(BATTLE), player)

{

}

void PlayerCastSpellAction::setup()
{
	//postcondition: displays spell choice menu to player to choose a spell to cast
	// in battle, and then target choices if there is more than one option.
	//if the player chooses to cancel out of choosing a spell, the action is
	//aborted.

	do
	{
		//Get spell choice first
		spellChooser.run();
		if(spellChooser.canceled())
		{
			return;
		}

		spellChoice = spellChooser.getChoice();

		//Prepare target list based on spell's eligible targts
		vector<Character*>* eligibleTargets = new vector<Character*>();
		const set<int> eligibleTargetOptions = spellChoice->getEligibleTargets();
		for(set<int>::const_iterator it = eligibleTargetOptions.begin(); it != eligibleTargetOptions.end(); it++)
		{
			switch(*it)
			{
			case PLAYER:
				eligibleTargets->push_back(&caster);
				break;
			case MONSTER:
				eligibleTargets->push_back(&enemy);
				break;
			}
		}

		//sanity check that there are actually eligible targets
		if(eligibleTargets->empty())
		{
			cout<<"No eligible targets for this spell! This is a bug; spell shouldn't be eligible to cast in this location."<<endl;
			delete eligibleTargets;
			return;
		}

		//If there is only 1 eligible target, don't bother asking player for target choice.
		if(eligibleTargets->size() == 1)
		{
			spellTarget = (*eligibleTargets)[0];
			delete eligibleTargets;
			return;
		}

		//Ask player to select a target for the spell
		TargetChooser targetChooser(eligibleTargets);
		targetChooser.run();
		if(targetChooser.canceled())
		{
			continue;
		}

		spellTarget = targetChooser.getChoice();
	}while(spellTarget == NULL);
}
