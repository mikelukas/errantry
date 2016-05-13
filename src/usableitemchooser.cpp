#include "usableitemchooser.h"
#include "statsdisplayer.h"

UsableItemChooser::UsableItemChooser(Player& player)
	: EquipmentChooser(player.getItemsAsVector()), //deleted in super-destructor
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
	for(int i=0; i < invChoices->size(); i++)
	{
		const Equipment* invEq = (*invChoices)[i]->pEquipment;

		std::ostringstream eqChoiceLabel;
		cout<<i+1<<") "<<invEq->getName();
		if((*invChoices)[i]->quantity > 1) {
			cout<<" (x"<<(*invChoices)[i]->quantity<<")";
		}
		cout<<endl;
	}
	cout<<endl;
}
