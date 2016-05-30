#include "spellchooser.h"

SpellChooser::SpellChooser(vector<const Spell*>* spellChoices, const Player& player)
	: InventoryChooser(spellChoices),
	  player(player)
{

}

SpellChooser::~SpellChooser()
{
	if(invChoices == NULL)
	{
		return;
	}

	delete invChoices;
}

void SpellChooser::displayRelevantStats() const
{
	StatsDisplayer::fullDisplayFor(player);
}

void SpellChooser::displayInventoryChoices() const
{
	for(int i = 0; i < invChoices->size(); i++)
	{
		ostringstream choiceNum;
		choiceNum<<i+1<<")";

		cout<<std::left<<setw(4)<<choiceNum.str(); displaySpellLine((*invChoices)[i]);
	}
	cout<<endl;
}

bool SpellChooser::validate() const
{
	//First make sure player chose a valid choice number
	if(!InventoryChooser<const Spell*>::validate())
	{
		return false;
	}

	//Next ensure they're not buying something they already have
	const Spell* chosenSpell = getChosenSpell();
	if(chosenSpell != NULL && player.hasSpell(chosenSpell))
	{
		cout<<"You already know '"<<chosenSpell->getName()<<"'!"<<endl;
		return false;
	}

	return true;
}

const Spell* SpellChooser::getChosenSpell() const
{
	//postcondition: returns spell pointer at the index the player chose
	//in invChoices, or NULL if they chose to exit

	if(choice == EXIT_CHOICE) {
		return NULL;
	}

	return (*invChoices)[choice-1];
}
