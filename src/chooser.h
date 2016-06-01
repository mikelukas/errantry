#ifndef SRC_CHOOSER_H_
#define SRC_CHOOSER_H_

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
const int CANCELED_CHOICE = 0;

/* Abstract base class unifying common functionality for listing choices to the
 * player, prompting for input, validating that input, and getting the player's
 * choice, either has the numerical value they entered or the data for that value.
 *
 * The way the list itself is rendered is left up to subclasses.
 *
 * Workflow of using a chooser is:
 * 1. Instantiate
 * 2. Call run()
 * 3. Call exitChosen() to test if they chose to cancel
 * 4. If they didn't cancel, getChoice() or getChoiceNum to get player choice
 */
template <typename T>
class Chooser
{
	protected:
		const vector<T*>* eligibleChoices;  //vector itself freed in destructor; contents will not individually be freed
		int choiceNum;

		virtual void displayChoiceMenu() const = 0;
		virtual void displayChoicePrompt() const;

		virtual bool validate() const;

	public:
		Chooser(const vector<T*>*);
		virtual ~Chooser();

		virtual void run();

		int getChoiceNum() const;
		T* getChoice() const;

		bool canceled() const;
};

#include "chooser.cpp"

#endif
