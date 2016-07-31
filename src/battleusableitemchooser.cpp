#include "battleusableitemchooser.h"

BattleUsableItemChooser::BattleUsableItemChooser(Player& player, const Monster& monster)
	: UsableItemChooser(player), //deleted in super-destructor
	  monster(monster)
{

}

void BattleUsableItemChooser::displayRelevantStats() const
{
	//postcondition:: All player and monster stats are displayed

	cout<<player.ShowName()<<endl;
	StatsDisplayer::battleMenuDisplayFor(player);
	cout<<endl;
	cout<<monster.ShowName()<<endl;
	StatsDisplayer::battleMenuDisplayFor(monster);
}
