#include "useitemaction.h"

UseItemAction::UseItemAction(Player& player, Monster& monster)
	: player(player),
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
		EquipmentChooser* itemChooser = new BattleUsableItemChooser(player, monster);
		itemChooser->display();

		//Get the choices out of the chooser now so we can delete right here
		int itemChoice = itemChooser->getChoice();
		pEquipmentChoice = itemChooser->getChosenEquipment();
		delete itemChooser;

		if(itemChoice == EXIT_CHOICE)
		{
			setAborted(true);
			return;
		}

		//Prompt player to choice a target for their item choice
		int targetChoice = 0;

		cout<<"**********************MESSAGES**********************"<<endl;
		cout<<"1)Player"<<endl
			<<"2)Monster"<<endl
			<<"0)Back"<<endl
			<<endl;
		cout<<"Choose a target:"<<endl;
		cin>>targetChoice;

		//Set mode target based on player choice, choice should only be able to be valid at this point
		switch(targetChoice)
		{
		case 1:
			setTarget(player);
			break;
		case 2:
			setTarget(monster);
			break;
		case EXIT_CHOICE:
			continue; //go back to choosing item again
		default:
			cout<<"Invalid response"<<endl;
			break;
		}
	} while(pTarget == NULL);
}

void UseItemAction::setTarget(Character& target)
{
	this->pTarget = &target;
}

void UseItemAction::execute()
{
	//postcondition: chosen item is used on the chosen target. Assumes these
	//pointers aren't null, since mode would've been aborted if either was

	player.useEquipment(pEquipmentChoice, *pTarget);
}
