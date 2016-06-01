#ifndef SRC_INVENTORYCHOOSER_H_
#define SRC_INVENTORYCHOOSER_H_

#include <vector>
#include "chooser.h"

using std::vector;

/* Abstract base class unifying common code for displaying inventory choices to
 * the player.
 * Subclasses provide specific functionality for stats displayed to the user which
 * might aid in making a decision, and listing the inventory itself.
 * Templated to be able to handle arbitrary items from player's inventory (e.g.
 * EquipmentLines and Spells)
 */
template <typename T>
class InventoryChooser : public Chooser<T>
{
	protected:

		virtual void displayRelevantStats() const = 0;
		virtual void displayInventoryChoices() const = 0;
		virtual void displayPostChoiceListInfo() const {}

		void displayChoiceMenu() const;

	public:
		InventoryChooser(const vector<T*>*);
		virtual ~InventoryChooser() {}
};

#include "inventorychooser.cpp"

#endif
