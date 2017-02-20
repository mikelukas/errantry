#ifndef SRC_SHOPTRANSACTIONMODE_H_
#define SRC_SHOPTRANSACTIONMODE_H_

#include <iomanip>
#include <iostream>
#include "gamemode.h"

using std::setw;
using std::cout;
using std::endl;

const int CANCELED_CHOICE = 0;

/* Base class for shop buying and selling shop modes, providing common functionality
 * to both for display choices and directing to appropriate specific logic for
 * handling the buy or sell, which will be implemented in subclasses.
 */
class ShopTransactionMode : public GameMode
{
	protected:
		vector<EquipmentLine*>* equipmentChoices;
		EquipmentLine* equipmentChoice;
		int choiceNum;

		virtual void updateDisplay();
		virtual bool processInput();

		void clearShopChoice();

		virtual void displayShopChoice(const EquipmentLine*) const = 0;
		virtual bool validateShopChoice(const Equipment*, int quantity) const = 0;
		virtual void processTransaction() = 0;
		virtual void updateChoices(int) {};

	public:
		ShopTransactionMode(vector<EquipmentLine*>*, GameData&, GameState&);
		virtual ~ShopTransactionMode();
};

#endif
