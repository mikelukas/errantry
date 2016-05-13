#include "inventorychooser.h"

template <class T>
InventoryChooser<T>::InventoryChooser(vector<T>* invChoices)
	: invChoices(invChoices),
	  choice(NO_CHOICE)
{

}

template <class T>
void InventoryChooser<T>::display()
{
	//postcondition: the player's current attributes relative to the type of
	//equipment they can apply in this mode are displayed, followed by eligible
	//equipment choices they can apply to themselves in this mode.

	cout<<"****************************************************"<<endl;
	displayRelevantStats();
	cout<<"----------------------------------------------------"<<endl;
	displayInventoryChoices();
	cout<<EXIT_CHOICE<<") Back"<<endl;
	cout<<"**********************MESSAGES**********************"<<endl;

	do
	{
		cout<<"Please choose an option:  "<<endl;
		cin>>choice;

		if(choice == EXIT_CHOICE)
		{
			return;
		}
	} while(!validate());
}

template <class T>
bool InventoryChooser<T>::validate() const
{
	//Even though EXIT_CHOICE is 0 right now, test explicitly like this to ensure if it changes things don't break
	if(choice != EXIT_CHOICE && (choice < 1 || choice > invChoices->size()))
	{
		cout<<"Invalid response."<<endl;
		return false;
	}

	return true;
}

template <class T>
int InventoryChooser<T>::getChoice() const
{
	//postcondition: returns the choice number the player selected after display()
	//is called, or NO_CHOICE if display() has never been called.

	return choice;
}
