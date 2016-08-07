#include "useitemaction.h"

UseItemAction::UseItemAction(Player& player, Monster& monster)
	: BattleAction(player),
	  player(player),
	  monster(monster),
	  pEquipmentChoice(NULL),
	  pTarget(NULL)
{

}

void UseItemAction::setup()
{
	//postcondition: an item from the player's inventory is set in pEquipmentChoice
	//and a target for the item is set in pTarget, or the mode is aborted by the
	//player and these are set to null

	do {
		BattleUsableItemChooser itemChooser(player, monster);
		itemChooser.run();
		if(itemChooser.canceled())
		{
			setAborted(true);
			return;
		}


		//Get the choices out of the chooser now so we can delete right here
		EquipmentLine* eqLine = itemChooser.getChoice();
		if(eqLine != NULL)
		{
			pEquipmentChoice = eqLine->pEquipment;
		}

		//Prompt player to choice a target for their item choice
		vector<Character*>* eligibleTargets = new vector<Character*>(); //freed in chooser deconstructor
		eligibleTargets->push_back(&player);
		eligibleTargets->push_back(&monster);

		TargetChooser targetChooser(eligibleTargets);
		targetChooser.run();
		if(targetChooser.canceled())
		{
			continue;
		}

		//Set mode target based on player choice, choice should only be able to be valid at this point
		setTarget(*(targetChooser.getChoice()));
	} while(pTarget == NULL);
}

void UseItemAction::setTarget(Character& target)
{
	this->pTarget = &target;
}

void UseItemAction::doAction()
{
	//postcondition: chosen item is used on the chosen target. Assumes these
	//pointers aren't null, since mode would've been aborted if either was

	cout<<player.ShowName()<<" used a "<<pEquipmentChoice->getName()<<" on "<<pTarget->ShowName()<<"!"<<endl;
	player.useEquipment(pEquipmentChoice, *pTarget);
}
