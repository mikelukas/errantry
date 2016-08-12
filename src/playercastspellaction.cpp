#include "playercastspellaction.h"

PlayerCastSpellAction::PlayerCastSpellAction(Player& player, Monster& monster)
	: CastSpellAction(player, monster),
	  spellChooser(player.getSpellsForLocale(BATTLE), player)

{

}

bool PlayerCastSpellAction::setupSpellChoice()
{
	//postcondition: asks the player to choose a spell, and sets spellChoice
	//with that spell if the player has enough MP to cast it.  If the player
	//cancels choosing, aborts this CastSpellAction, completely.
	//returns true if spell can be cast and setup should move on to next step,
	//and false if we should stay on this step.

	//Get spell choice first
	spellChooser.run();
	if(spellChooser.canceled())
	{
		setAborted(true);
		return false;
	}

	spellChoice = spellChooser.getChoice();
	if(!caster.hasEnoughMpFor(spellChoice))
	{
		cout<<"Not enough MP to cast '"<<spellChoice->getName()<<"'."<<endl;
		return false;
	}

	return true;
}

bool PlayerCastSpellAction::setupTargetChoice()
{
	//postcondition: gets eligible targets for the chosen spell, and asks
	//the player to choose from them if there is more than 1.  If there is only
	//one, automatically chooses the spell's target without asking.
	//returns true if this CastSpellAction should move on to the next setup step
	//and false if it should move back to the previous one.

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
		return false;
	}

	//If there is only 1 eligible target, don't bother asking player for target choice.
	if(eligibleTargets->size() == 1)
	{
		spellTarget = (*eligibleTargets)[0];
		delete eligibleTargets;
		return true;
	}

	//Ask player to select a target for the spell
	TargetChooser targetChooser(eligibleTargets);
	targetChooser.run();
	if(targetChooser.canceled())
	{
		return false;
	}

	spellTarget = targetChooser.getChoice();
	return true;
}
