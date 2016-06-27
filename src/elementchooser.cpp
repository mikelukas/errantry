#include "elementchooser.h"

ElementChooser::ElementChooser()
	: Chooser<const Element>(buildElementPointerVector())
{
	cancelAllowed = false;
}

void ElementChooser::displayChoiceMenu() const
{
	//postcondition: displays a list of elements and choice numbers.
	for(int i=0; i < ELEMENTS.size()-1; i++)
	{
		displayChoice(i, (*eligibleChoices)[i]);
	}
}

void ElementChooser::displayChoice(int choiceNum, const Element* choice) const
{
	//postcondition: displays the element name and its choice number

	cout<<choiceNum+1<<") "<<getDisplayNameFor(*choice)<<endl;
}

void ElementChooser::displayChoicePrompt() const
{
	cout<<": ";
}
