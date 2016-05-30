#include "spellchooser.h"

SpellChooser::SpellChooser(const Player& player)
	: InventoryChooser(player.getSpells()),
	  player(player)
{

}

SpellChooser::SpellChooser(const Player& player, SpellLocale spellLocale)
	: InventoryChooser(player.getSpellsForLocale(spellLocale)),
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

const Spell* SpellChooser::getChosenSpell() const
{
	//postcondition: returns spell pointer at the index the player chose
	//in invChoices, or NULL if they chose to exit

	if(choice == EXIT_CHOICE) {
		return NULL;
	}

	return (*invChoices)[choice-1];
}
