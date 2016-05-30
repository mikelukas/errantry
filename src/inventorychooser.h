#ifndef SRC_INVENTORYCHOOSER_H_
#define SRC_INVENTORYCHOOSER_H_

#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::vector;

const int NO_CHOICE = -1;
const int EXIT_CHOICE = 0;

/* Abstract base class unifying common code for displaying inventory choices to
 * the player, validating their choice, and retrieving the index (starting at 1)
 * of the choice they made.
 * Subclasses provide specific functionality for stats displayed to the user which
 * might aid in making a decision, and listing the inventory itself.
 * Templated since type of stuff in the player's inventory can be arbitrary.
 */
template <class T>
class InventoryChooser
{
	protected:
		vector<T>* invChoices; //it is up to subclasses to decide how this is freed
		int choice;

		virtual void displayRelevantStats() const = 0;
		virtual void displayInventoryChoices() const = 0;
		virtual void displayPostChoiceListInfo() const {}

		virtual bool validate() const;

	public:
		InventoryChooser(vector<T>*);
		virtual ~InventoryChooser() {}

		void display();

		int getChoice() const;
};

#include "inventorychooser.cpp"

#endif
