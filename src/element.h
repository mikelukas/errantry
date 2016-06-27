#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

/* Most spells have an Element, which amplifies the effect of the spell if the
 * target is weak toward that element.
 * Every element has an opposite - elements in this enum are listed in pairs of
 * opposites.
 *
 * NOTE if adding/removing elements here, or changing order, update vectorizeElements()
 */
enum Element
{
	fire, water,
	air, earth,

	none
};

vector<Element> vectorizeElements();
const vector<const Element*>* buildElementPointerVector();
Element getOppositeOf(Element);
string getDisplayNameFor(Element);

const vector<Element> ELEMENTS = vectorizeElements();
#endif
