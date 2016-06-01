#include "chooser.h"

template <typename T>
Chooser<T>::Chooser(const vector<T*>* eligibleChoices)
	: eligibleChoices(eligibleChoices),
	  choiceNum(NO_CHOICE)
{

}

template <typename T>
Chooser<T>::~Chooser()
{
	//postcondition: eligibleChoices freed; assumes subclasses allocated it at creation

	if(eligibleChoices == NULL)
	{
		return;
	}

	delete eligibleChoices;
}

template <typename T>
void Chooser<T>::run()
{
	//postcondition: displays the available choices to the player, and requests
	//input until that input is valid.
	//choice display and validation are left up to subclasses;

	displayChoiceMenu();

	do
	{
		displayChoicePrompt();
		cin>>choiceNum;

		if(canceled())
		{
			return;
		}
	} while(!validate());
}

template <typename T>
void Chooser<T>::displayChoicePrompt() const
{
	cout<<"Please choose an option:  ";
}

template <typename T>
bool Chooser<T>::validate() const
{
	//postcondition: returns true if the player chose the exit value, or entered
	//a number that is a valid index in the eligibleChoices vector
	//returns false otherwise.

	//Even though EXIT_CHOICE is 0 right now, test explicitly like this to ensure if it changes things don't break
	if(getChoiceNum() != CANCELED_CHOICE && (getChoiceNum() < 1 || getChoiceNum() > eligibleChoices->size()))
	{
		cout<<"Invalid response."<<endl;
		return false;
	}

	return true;
}

template <typename T>
int Chooser<T>::getChoiceNum() const
{
	//postcondition: returns the choice number the player selected after display()
	//is called, or NO_CHOICE if display() has never been called.

	return choiceNum;
}

template <typename T>
T* Chooser<T>::getChoice() const
{
	//postcondition: returns a pointer to the actual data represented by the
	//numerical choice the player made from the menu, or NULL if they chose to exit

	if(canceled()) {
		return NULL;
	}

	return (*eligibleChoices)[getChoiceNum()-1];
}

template <typename T>
bool Chooser<T>::canceled() const
{
	//postcondition: returns true if the player chosen the exit option from the
	//menu, false otherwise.

	return getChoiceNum() == CANCELED_CHOICE;
}
