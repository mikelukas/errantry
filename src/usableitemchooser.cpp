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
		const Equipment* invEq = (*eligibleChoices)[i]->pEquipment;

		std::ostringstream eqChoiceLabel;
		cout<<i+1<<") "<<invEq->getName();
		if((*eligibleChoices)[i]->quantity > 1) {
			cout<<" (x"<<(*eligibleChoices)[i]->quantity<<")";
		}
		cout<<endl;
	}
	cout<<endl;
}
