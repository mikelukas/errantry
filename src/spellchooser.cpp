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

bool SpellChooser::validate() const
{
	//First make sure player chose a valid choice number
	if(!Chooser::validate())
	{
		return false;
	}

	//Next ensure they're not buying something they already have
	const Spell* chosenSpell = getChoice();
	if(chosenSpell != NULL && player.hasSpell(chosenSpell))
	{
		cout<<"You already know '"<<chosenSpell->getName()<<"'!"<<endl;
		return false;
	}

	return true;
}
