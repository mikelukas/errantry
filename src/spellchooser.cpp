#include "spellchooser.h"

SpellChooser::SpellChooser(vector<const SpellTemplate*>* spellChoices, const Player& player)
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
		displayChoice(i, (*eligibleChoices)[i]);
	}
	cout<<endl;
}

void SpellChooser::displayChoice(int choiceNum, const SpellTemplate* spellChoice) const
{
	ostringstream choiceNumStr;
	choiceNumStr<<choiceNum+1<<")";

	cout<<std::left<<setw(4)<<choiceNumStr.str(); displaySpellLine(spellChoice);
}
