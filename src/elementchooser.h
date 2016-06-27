#ifndef SRC_ELEMENTCHOOSER_H_
#define SRC_ELEMENTCHOOSER_H_

#include "character.h"
#include "chooser.h"
#include "element.h"

/* Displays list of elements and prompts for a choice.  Not cancelable, since
 * intended to be used for effects
 */
class ElementChooser : public Chooser<const Element>
{
	protected:

		virtual void displayChoiceMenu() const;
		virtual void displayChoice(int, const Element*) const;
		virtual void displayChoicePrompt() const;

	public:
		ElementChooser();
		virtual ~ElementChooser() {}
};

#endif
