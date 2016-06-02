#include "castspellchooser.h"

CastSpellChooser::CastSpellChooser(vector<const Spell*>* spellChoices, const Player& player)
	: SpellChooser(spellChoices, player)
{

}

void CastSpellChooser::displayInventoryChoices() const
{
	//postcondition: displays heading above the spell choices, describing
	//relevant stats shown for each spell.

	cout<<std::right<<setw(8)<<"Name"<<setw(18)<<"Element"<<setw(10)<<"MP"<<endl;
	SpellChooser::displayInventoryChoices();
}

void CastSpellChooser::displaySpellLine(const Spell* spell) const
{
	//postcondition: displays the name, element, and MP cost of the given spell.

	cout<<setw(15)<<spell->getName()<<setw(14)<<getDisplayNameFor(spell->getElement())<<" "<<setw(3)<<spell->getMpCost()<<endl;
}
