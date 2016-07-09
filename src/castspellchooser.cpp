#include "castspellchooser.h"

CastSpellChooser::CastSpellChooser(vector<const SpellTemplate*>* spellChoices, const Player& player)
	: SpellChooser(spellChoices, player),
	  uncastableSpells(NULL)
{

}

CastSpellChooser::CastSpellChooser(vector<const SpellTemplate*>* spellChoices, vector<const SpellTemplate*>* uncastableSpells, const Player& player)
	: SpellChooser(spellChoices, player),
	  uncastableSpells(uncastableSpells)
{

}

CastSpellChooser::~CastSpellChooser()
{
	if(uncastableSpells != NULL)
	{
		delete uncastableSpells;
	}
}

void CastSpellChooser::displayInventoryChoices() const
{
	//postcondition: displays heading above the spell choices, describing
	//relevant stats shown for each spell.

	cout<<std::right<<setw(8)<<"Name"<<setw(18)<<"Element"<<setw(10)<<"MP"<<endl
		<<endl;
	if(uncastableSpells != NULL && !uncastableSpells->empty())
	{
		cout<<"Uncastable:"<<endl;
		for(int i=0; i < uncastableSpells->size(); i++)
		{
			cout<<"    "; displaySpellLine((*uncastableSpells)[i]);
		}
		cout<<endl;
	}

	cout<<"Castable:"<<endl;
	SpellChooser::displayInventoryChoices();
}

void CastSpellChooser::displaySpellLine(const SpellTemplate* spell) const
{
	//postcondition: displays the name, element, and MP cost of the given spell.

	cout<<std::left<<setw(15)<<spell->getName()<<setw(14)<<getDisplayNameFor(spell->getElement())<<" "<<setw(3)<<spell->getMpCost()<<endl;
}
