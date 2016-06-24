#include "usableitemchooser.h"
#include "statsdisplayer.h"

UsableItemChooser::UsableItemChooser(Player& player)
	: InventoryChooser<EquipmentLine>(player.getItemsAsVector()), //deleted in super-destructor
	  player(player)
{

}

void UsableItemChooser::displayRelevantStats() const
{
	//postcondition:: All player stats are listed

	StatsDisplayer::fullDisplayFor(player);
}

void UsableItemChooser::displayInventoryChoices() const
{
	//postcondition: All Item equipment the player has in their inventory is listed

	cout<<"Items"<<endl;
	for(int i=0; i < eligibleChoices->size(); i++)
	{
		displayChoice(i, (*eligibleChoices)[i]);
	}
	cout<<endl;
}

void UsableItemChooser::displayChoice(int choiceNum, EquipmentLine* eqLine) const
{
	const Equipment* invEq = eqLine->pEquipment;

	std::ostringstream eqChoiceLabel;
	cout<<choiceNum+1<<") "<<invEq->getName();
	if(eqLine->quantity > 1) {
		cout<<" (x"<<eqLine->quantity<<")";
	}
	cout<<endl;
}
