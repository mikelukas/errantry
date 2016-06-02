#include "spellchooser.h"

SpellChooser::SpellChooser(vector<const Spell*>* spellChoices, const Player& player)
	: InventoryChooser(spellChoices),
	  player(player)
{

}

void SpellChooser::displayRelevantStats() const
{
	StatsDisplayer::fullDisplayFor(player);
}

void SpellChooser::displayInventoryChoices() const
{
	for(int i = 0; i < eligibleChoices->size(); i++)
	{
		ostringstream choiceNum;
		choiceNum<<i+1<<")";

		cout<<std::left<<setw(4)<<choiceNum.str(); displaySpellLine((*eligibleChoices)[i]);
	}
	cout<<endl;
}
