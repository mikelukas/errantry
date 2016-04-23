#include "gamestate.h"
#include "statsdisplayer.h"
#include "useitemmode.h"

UseItemMode::UseItemMode(GameData& gameData, GameState& gameState)
	: ApplyEquipmentMode(gameData, gameState)
{

}

void UseItemMode::displayRelevantPlayerAttrs()
{
	StatsDisplayer::fullDisplayFor(gameState.getPlayer());
}

void UseItemMode::displayEquipmentList()
{
	cout<<"Items"<<endl;
	for(int i=0; i < invEquipment->size(); i++)
	{
		const Equipment* invEq = (*invEquipment)[i]->pEquipment;

		std::ostringstream eqChoiceLabel;
		cout<<i+1<<") "<<invEq->getName();
		if((*invEquipment)[i]->quantity > 1) {
			cout<<" (x"<<(*invEquipment)[i]->quantity<<")";
		}
		cout<<endl;
	}
	cout<<endl;
}

void UseItemMode::updateEquipmentChoices()
{
	//postcondition: populates invEquipment with dynamically allocated vector of
	//items.  invEquipment will be freed by cleanupEquipmentChoices()

	invEquipment = gameState.getPlayer().getItemsAsVector();
}
