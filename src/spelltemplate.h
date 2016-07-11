#ifndef _SPELL_H
#define _SPELL_H

#include <istream>
#include <set>
#include <string>
#include <vector>
#include "element.h"
#include "streamutils.h" //getIdLine

using std::istream;
using std::set;
using std::string;
using std::vector;

const int NUM_SPELL_CATEGORIES = 4;
enum SpellCategory {ATTACK, HEALING, OFFENSIVE_ASSIST, DEFENSIVE_ASSIST};
enum SpellLocale {FIELD, BATTLE};
enum TargetType {PLAYER, MONSTER};

/* This class contains all information about a spell, but can't actually be cast.
 * Instead, a CastableSpell (subclass) should be created given a SpellTemplate
 * to copy. See CastableSpell for more information about how to cast one.
 * SpellTemplates reference 1 or more Effect IDs, which contain the actual logic
 * used when casting the spell. EFfect IDs allows SpellTemplates to be defined
 * in dat files without compilation, while still being able to do more complicated,
 * reusable logic that is not easily described in a standard way in dat files.
 */
class SpellTemplate
{
	protected:
		string name;                //display name of spell
		SpellCategory category;		//how the spell's effect can be summarized; used by monsters to decide on spells

		Element element;            //basic elemental type of spell

		int mpCost;   	            //cost in MP
		int purchasePrice;          //cost to learn (if learnable in a town)

		set<int> eligibleLocations; //locations where this spell can be cast
		set<int> eligibleTargets;	//targets player can choose for this spell

		vector<int> effectIds;	    //Effect IDs applied when this spell is cast, in order of application

	public:
		SpellTemplate(istream&);

		const string& getName() const;
		const SpellCategory getCategory() const;
		const Element getElement() const;
		const int getMpCost() const;
		const int getPurchasePrice() const;

		const set<int>& getEligibleLocations() const;
		const set<int>& getEligibleTargets() const;
};
    
#endif
